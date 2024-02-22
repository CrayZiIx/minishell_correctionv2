/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:24:30 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/21 05:45:47 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

static char	*find_command(char **env_path, char *cmd,
	char *full_path, t_glob *g_global)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		temp = ft_strjoin(env_path[i], "/", &g_global->gc);
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd, &g_global->gc);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
		return (NULL);
	return (full_path);
}

static DIR	*cmd_checks(t_pt *pt, t_list *cmd, char ***s, char *path)
{
	t_input	*node;
	DIR		*dir;

	dir = NULL;
	node = cmd->content;
	if (node && node->full_cmd)
		dir = opendir(*node->full_cmd);
	if (node && node->full_cmd && ft_strchr(*node->full_cmd, '/') && !dir)
	{
		*s = ft_split(*node->full_cmd, '/', &pt->g_global->gc);
		node->full_path = ft_strdup(*node->full_cmd, &pt->g_global->gc);
		node->full_cmd[0] = ft_strdup(s[0][ft_matrixlen(*s) - 1],
				&pt->g_global->gc);
	}
	else if (!is_builtins(node) && node && node->full_cmd && !dir)
	{
		path = ft_getenv("PATH", pt->prompt->envp, 4, pt->g_global);
		*s = ft_split(path, ':', &pt->g_global->gc);
		node->full_path = find_command(*s, *node->full_cmd,
				node->full_path, pt->g_global);
		if (!node->full_path || !node->full_cmd[0] || !node->full_cmd[0][0])
			ft_perror(NOT_CMD, *node->full_cmd, 127, pt->g_global);
	}
	return (dir);
}

static void	get_cmd(t_pt *pt, t_list *cmd, char **s, char *path)
{
	t_input	*node;
	DIR		*dir;

	node = cmd->content;
	dir = cmd_checks(pt, cmd, &s, path);
	if (!is_builtins(node) && node && node->full_cmd && dir)
		ft_perror(IS_DIR, *node->full_cmd, 126, pt->g_global);
	else if (!is_builtins(node) && node && node->full_path && \
		access(node->full_path, F_OK) == -1)
		ft_perror(NOT_DIR, node->full_path, 127, pt->g_global);
	else if (!is_builtins(node) && node && node->full_path && \
		access(node->full_path, X_OK) == -1)
		ft_perror(NO_PERM, node->full_path, 126, pt->g_global);
	if (dir)
		closedir(dir);
	ft_free_matrix(&s);
}

void	*exec_cmd(t_prompt *prompt, t_list *cmd, t_glob *g_global)
{
	int		fd[2];
	t_pt	pt;

	pt.prompt = prompt;
	pt.g_global = g_global;
	get_cmd(&pt, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (ft_perror(PIPE_ERR, NULL, 1, g_global));
	if (!check_to_fork(prompt, cmd, fd, g_global))
		return (NULL);
	ft_close(fd[WRITE_END]);
	if (cmd->next && !((t_input *)cmd->next->content)->pipein)
		((t_input *)cmd->next->content)->pipein = fd[READ_END];
	else
		ft_close(fd[READ_END]);
	if (((t_input *)cmd->content)->pipein > 2)
		ft_close(((t_input *)cmd->content)->pipein);
	if (((t_input *)cmd->content)->pipeout > 2)
		ft_close(((t_input *)cmd->content)->pipeout);
	return (NULL);
}

int	check_arg(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]) == 1)
		return (printf(" : export: `%s': not a valid identifier\n", str), 1);
	i ++;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == ' ')
			return (printf("export: `%c': not a valid identifier \n",
					str[i - 1]), 1);
		if (ft_isalpha(str[i]) == 1 || str[i] == '_'
			|| ft_isalnum(str[i]) == 1 || str[i])
			i ++;
		else
			return (1);
	}
	if (str[0] == ' ')
		return (1);
	return (0);
}
