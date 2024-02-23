/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:31:58 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/22 19:31:47 by mamottet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

static char	**split_all(char **args, t_prompt *prompt, t_glob *g_global)
{
	char		**subsplit;
	int			i;
	int			quotes[2];
	t_pt		pt;
	t_double_sg	dsg;	

	dsg.set = ft_getenv("HOME", prompt->envp, 4, g_global);
	pt.g_global = g_global;
	pt.prompt = prompt;
	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, &pt);
		args[i] = expand_path(args[i], -1, quotes, &dsg);
		subsplit = ft_cmdsubsplit(args[i], "<|>", g_global);
		ft_matrix_replace_in(&args, subsplit, i, g_global);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

static void	*parse_args(char **args, t_prompt *p, t_glob *g_global)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmds = fill_nodes(split_all(args, p, g_global), -1, g_global);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_global->g_state = builtins(p, p->cmds, &is_exit, g_global);
	while (i-- > 0)
		waitpid(-1, &g_global->g_state, 0);
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

void	*check_args(char *out, t_prompt *p, t_glob *g_global)
{
	char	**a;
	t_input	*n;

	if (!out)
		return (NULL);
	if (out[0] != '\0')
		add_history(out);
	a = ft_cmdtrim(out, " ", g_global);
	if (!a)
		return (ft_perror(QUOTE, NULL, 1, g_global), "");
	if (ft_matrixlen(a) == 1 && is_redir_like(a[0]) == 0)
	{
		syntax_error(SYNTAXE_REDIR, NULL, g_global);
		return ("");
	}
	p = parse_args(a, p, g_global);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = ft_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
			p->envp, g_global);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
