/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:58:07 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/20 21:46:40 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

static t_input	*ft_init(t_glob *g_global)
{
	t_input	*input;

	input = gc_malloc(&g_global->gc, sizeof(t_input));
	if (!input)
		return (NULL);
	input->full_cmd = NULL;
	input->full_path = NULL;
	input->pipein = STDIN_FILENO;
	input->pipeout = STDOUT_FILENO;
	return (input);
}

static t_input	*get_params(t_input *node, char **a[2],
	int *i, t_glob *g_global)
{
	if (a[0][*i] && whath_is(a, i))
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] != '<'
			&& a[0][*i + 1][0] != '>')
			node = get_pipeout1(node, a[1], i, g_global);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] != '>'
			&& a[0][*i + 1][0] != '<' )
			node = get_pipein1(node, a[1], i, g_global);
		else if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_pipeout2(node, a[1], i, g_global);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = get_pipein2(node, a[1], i, g_global);
		else if (a[0][*i][0] != '|')
			node->full_cmd = ft_extend_matrix(node->full_cmd, a[1][*i],
					g_global);
		return (node);
	}
	ft_perror(PIPES_ERR, NULL, 2, g_global);
	*i = -2;
	return (node);
}

static char	**get_trimmed(char **args, t_glob *g_global)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_dup_matrix(args, g_global);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0, g_global);
		temp[j] = aux;
	}
	return (temp);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_free_matrix(&temp);
	ft_free_matrix(&args);
	return (NULL);
}

t_list	*fill_nodes(char **args, int i, t_glob *g_global)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = get_trimmed(args, g_global);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(ft_init(g_global)));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = get_params(cmds[1]->content, temp, &i, g_global);
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	ft_free_matrix(&temp[1]);
	ft_free_matrix(&args);
	return (cmds[0]);
}
