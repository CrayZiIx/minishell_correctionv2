/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 02:27:04 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 15:02:48 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_sig_int;

static void	child_builtin(t_pt *pt, t_input *node, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtins(node) && node->full_cmd)
		execve(node->full_path, node->full_cmd, pt->prompt->envp);
	else if (is_builtins(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "pwd", l) && l == 3)
		pt->g_global->g_state = ft_pwd();
	else if (is_builtins(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "echo", l) && l == 4)
		pt->g_global->g_state = ft_echo(cmd);
	else if (is_builtins(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "env", l) && l == 3)
		pt->g_global->g_state = ft_env(pt, cmd);
	else if (is_builtins(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "export", l) && l == 6)
		pt->g_global->g_state = ft_export(pt->prompt, pt->g_global);
}
	// else if (is_builtins(node) && node->full_cmd && \
	// 	!ft_strncmp(*node->full_cmd, "exit", l) && l == 4)
	// 	pt->g_global->g_state = ft_exit(pt, cmd);

static void	*child_redir(t_list *cmd, int fd[2], t_glob *g_global)
{
	t_input	*node;

	node = cmd->content;
	if (node->pipein != STDIN_FILENO)
	{
		if (dup2(node->pipein, STDIN_FILENO) == -1)
			return (ft_perror(DUP_ERR, NULL, 1, g_global));
		ft_close(node->pipein);
	}
	if (node->pipeout != STDOUT_FILENO)
	{
		if (dup2(node->pipeout, STDOUT_FILENO) == -1)
			return (ft_perror(DUP_ERR, NULL, 1, g_global));
		ft_close(node->pipeout);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (ft_perror(DUP_ERR, NULL, 1, g_global));
	ft_close(fd[WRITE_END]);
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
	ft_close(fd[READ_END]);
	child_builtin(&pt, node, l, cmd);
	wait(&g_global->g_state);
	if (g_sig_int == 1)
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
		ft_close(fd[READ_END]);
		ft_close(fd[WRITE_END]);
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
