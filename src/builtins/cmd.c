/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamottet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:47:46 by mamottet          #+#    #+#             */
/*   Updated: 2024/02/22 15:47:48 by mamottet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_cd(t_prompt *p, t_glob *g_global)
{
	char	**str[2];
	char	*aux;

	g_global->g_state = 0;
	str[0] = ((t_input *)p->cmds->content)->full_cmd;
	aux = ft_getenv("HOME", p->envp, 4, g_global);
	if (!aux)
		aux = ft_strdup("", &g_global->gc);
	str[1] = ft_extend_matrix(NULL, aux, g_global);
	cd_error(str, g_global);
	if (!g_global->g_state)
		p->envp = ft_setenv("OLDPWD", str[1][1], p->envp, g_global);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("", &g_global->gc);
	str[1] = ft_extend_matrix(str[1], aux, g_global);
	free(aux);
	p->envp = ft_setenv("PWD", str[1][2], p->envp, g_global);
	ft_free_matrix(&str[1]);
	return (g_global->g_state);
}

void	ft_pwd(t_list *cmd, t_glob *g_global)
{
	char	*buf;
	t_input	*node;

	node = cmd->content;
	if (node->full_cmd[1] == NULL)
	{
		buf = getcwd(NULL, 4096);
		ft_putendl_fd(buf, 1);
		free(buf);
		g_global->g_state = 0;
	}
	else
		syntax_error(ARG_ERROR, "pwd", 1, g_global);
}

int	ft_echo(t_list *cmd)
{
	int		nl;
	int		i[2];
	char	**argv;
	t_input	*node;

	i[0] = 0;
	i[1] = 0;
	nl = 1;
	node = cmd->content;
	argv = node->full_cmd;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && \
			(ft_countchar(argv[i[0]], 'n') == \
			(int)(ft_strlen(argv[i[0]]) - 1)))
			nl = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", nl) == 2);
}
