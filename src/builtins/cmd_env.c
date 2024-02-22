/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:50:59 by mamottet          #+#    #+#             */
/*   Updated: 2024/02/22 17:37:35 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export(t_prompt *prompt, t_glob *g_global)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_input *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2 && argv[1] != NULL && check_arg(argv[1]) == 0)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], prompt->envp, ij);
			if (pos == 1)
				prompt->envp[ij[1]] = ft_strdup(argv[ij[0]], &g_global->gc);
			else if (!pos)
				prompt->envp = ft_extend_matrix(prompt->envp,
						argv[ij[0]], g_global);
			ij[0]++;
		}
	}
	else if (!argv[1])
	{
		ft_putmatrix_fd(prompt->envp, 1, 1);
		g_global->g_state = 0;
	}
	return (0);
}

int	ft_unset(t_prompt *prompt, t_glob *g_global)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_input *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[ij[0]], "=", &g_global->gc);
				argv[ij[0]] = aux;
			}
			if (var_in_envp(argv[ij[0]], prompt->envp, ij))
				ft_matrix_replace_in(&prompt->envp, NULL, ij[1], g_global);
		}
	}
	return (0);
}

int	ft_env(t_pt *pt, t_list *cmd)
{
	t_input	*node;

	node = cmd->content;
	if (node->full_cmd[1] == NULL)
	{
		ft_putmatrix_fd(pt->prompt->envp, 1, 1);
		return (0);
	}
	else
	{
		syntax_error(ARG_ERROR, node->full_cmd, pt->g_global);
		return (127);
	}
}
