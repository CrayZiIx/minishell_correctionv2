/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:29:46 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/21 14:06:45 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtins(t_prompt *prompt, t_list *cmd, int *is_exit, t_glob *g_global)
{
	char	**a;

	while (cmd)
	{
		a = ((t_input *)cmd->content)->full_cmd;
		if (a && !ft_strncmp(*a, "exit", ft_strlen("exit")) \
				&& ft_strlen("exit") == 4)
			g_global->g_state = ft_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", ft_strlen("cd")) \
				&& ft_strlen("cd") == 2)
			g_global->g_state = ft_cd(prompt, g_global);
		else if (!cmd->next && a \
				&& !ft_strncmp(*a, "export", ft_strlen("export")) \
				&& ft_strlen("export") == 6)
			g_global->g_state = ft_export(prompt, g_global);
		else if (!cmd->next && a \
			&& !ft_strncmp(*a, "unset", ft_strlen("unset")) \
			&& ft_strlen("unset") == 5)
			g_global->g_state = ft_unset(prompt, g_global);
		else
			exec_cmd(prompt, cmd, g_global);
		cmd = cmd->next;
	}
	return (g_global->g_state);
}

int	is_builtins(t_input *node)
{
	int	l;

	if (!node->full_cmd)
		return (0);
	if ((node->full_cmd && ft_strchr(*node->full_cmd, '/')) \
		|| (node->full_path && \
		ft_strchr(node->full_path, '/')))
		return (0);
	l = ft_strlen(*node->full_cmd);
	if (!ft_strncmp(*node->full_cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}

