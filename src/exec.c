/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 02:27:04 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/20 21:44:36 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

static void	child_builtin(t_pt *pt, t_input *node, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtins(node) && node->full_cmd)
		execve(node->full_path, node->full_cmd, pt->prompt->envp);
	else if (is_builtins(node) && node->full_cmd \
		&& !ft_strncmp(*node->full_cmd, "pwd", l) \
		&& l == 3)
		pt->g_global->g_state = ft_pwd();
	else if (is_builtins(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "echo", l) && l == 4)
		pt->g_global->g_state = ft_echo(cmd);
	else if (is_builtins(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "env", l) && l == 3)
	{
		ft_putmatrix_fd(pt->prompt->envp, 1, 1);
		pt->g_global->g_state = 0;
	}
}

static void	*child_redir(t_list *cmd, int fd[2], t_glob *g_global)
{
	t_input	*node;

	node = cmd->content;
	if (node->pipein != STDIN_FILENO)
	{
		if (dup2(node->pipein, STDIN_FILENO) == -1)
			return (ft_perror(DUP_ERR, NULL, 1, g_global));
		close(node->pipein);
	}
	if (node->pipeout != STDOUT_FILENO)
	{
		if (dup2(node->pipeout, STDOUT_FILENO) == -1)
			return (ft_perror(DUP_ERR, NULL, 1, g_global));
		close(node->pipeout);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (ft_perror(DUP_ERR, NULL, 1, g_global));
	close(fd[WRITE_END]);
	return ("");
}

static void	*child_process(t_prompt *prompt, t_list *cmd,
	int fd[2], t_glob	*g_global)
{
	t_input	*node;
	int		l;
	t_pt	pt;

	pt.prompt = prompt;
	pt.g_global = g_global;
	node = cmd->content;
	l = 0;
	if (node->full_cmd)
		l = ft_strlen(*node->full_cmd);
	child_redir(cmd, fd, g_global);
	close(fd[READ_END]);
	child_builtin(&pt, node, l, cmd);
	wait(&g_global->g_state);
	g_global->g_state = WEXITSTATUS(pt.g_global->g_state);
	ft_lstclear(&pt.prompt->cmds, free_content);
	gc_clean(&g_global->gc);
	exit(g_global->g_state);
}

static void	exec_fork(t_prompt *prompt, t_list *cmd,
	int fd[2], t_glob	*g_global)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		ft_perror(FORK_ERR, NULL, 1, g_global);
	}
	else if (!pid)
		child_process(prompt, cmd, fd, g_global);
	else
		wait(&g_global->g_state);
}

void	*check_to_fork(t_prompt *prompt, t_list *cmd,
	int fd[2], t_glob	*g_global)
{
	t_input	*node;
	DIR		*dir;

	node = cmd->content;
	dir = NULL;
	if (node->full_cmd)
		dir = opendir(*node->full_cmd);
	if (node->pipein == -1 || node->pipeout == -1)
		return (NULL);
	if ((node->full_path && access(node->full_path, X_OK) == 0) \
		|| is_builtins(node))
		exec_fork(prompt, cmd, fd, g_global);
	else if (!is_builtins(node) && ((node->full_path && \
		!access(node->full_path, F_OK)) || dir))
		g_global->g_state = 126;
	else if (!is_builtins(node) && node->full_cmd)
		g_global->g_state = 127;
	if (dir)
		closedir(dir);
	return ("");
}
