/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:26:58 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/27 15:34:34 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

int	get_fd(int oldfd, char *path, int flags[2], t_glob *g_global)
{
	int		fd;
	char	*s;
	char	*cwd;

	cwd = getcwd(NULL, 4096);
	s = ft_strjoin(cwd, "/", &g_global->gc);
	s = ft_strjoin(s, path, &g_global->gc);
	if (oldfd > 2)
		ft_close(oldfd);
	if (!path)
		return (-1);
	if (access(s, F_OK) == -1 && !flags[0])
		ft_perror(NOT_DIR, path, 127, g_global);
	if (!flags[0] && access(s, R_OK) == -1)
		ft_perror(NO_PERM, path, 126, g_global);
	if (!flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	free(cwd);
	return (fd);
}

t_input	*get_pipeout1(t_input *node, char **args, int *i, t_glob *g_global)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (args[*i])
		node->pipeout = get_fd(node->pipeout, args[*i], flags, g_global);
	if (!args[*i] || node->pipeout == -1)
	{
		*i = -1;
		if (node->pipeout != -1)
			print_error_heredoc('0', i, g_global);
		else
			g_global->g_state = 1;
	}
	return (node);
}

t_input	*get_pipeout2(t_input *node, char **args, int *i, t_glob *g_global)
{
	int	flags[2];

	flags[0] = 1;
	flags[1] = 0;
	if (args[(*i) + 2] && (args[(*i) + 2][0] == '<' \
		|| args[(*i) + 2][0] == '>'))
	{
		(*i) += 2;
		print_error_heredoc(args[2][0], i, g_global);
		return (node);
	}
	if (args[(*i) + 2])
		node->pipeout = get_fd(node->pipeout, args[(*i) += 2], flags, g_global);
	if (!args[*i] || node->pipeout == -1)
	{
		*i = -1;
		if (node->pipeout != -1)
		{
			print_error_heredoc('0', i, g_global);
		}
		else
			g_global->g_state = 1;
	}
	return (node);
}

t_input	*get_pipein1(t_input *node, char **args, int *i, t_glob *g_global)
{
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	(*i)++;
	if (args[*i])
		node->pipein = get_fd(node->pipein, args[*i], flags, g_global);
	if (!args[*i] || node->pipein == -1)
	{
		*i = -1;
		if (node->pipein != -1)
			print_error_heredoc('0', i, g_global);
		else
			g_global->g_state = 1;
	}
	return (node);
}

t_input	*get_pipein2(t_input *node, char **args, int *i, t_glob *g_global)
{
	char	*aux[2];
	char	*str[2];

	ft_strnull(str, 2);
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	if (args[(*i) + 2] && (args[(*i) + 2][0] == '<'
		|| args[(*i) + 2][0] == '>'))
	{
		print_error_heredoc(args[(*i) + 2][0], i, g_global);
		return (node);
	}
	(*i)++;
	if (args[++(*i)])
	{
		aux[0] = args[(*i)];
		node->pipein = get_here_doc(str, aux, g_global);
	}
	if (!args[*i] || node->pipein == -1)
	{
		*i = -1;
		if (node->pipein != -1)
			print_error_heredoc('0', i, g_global);
	}
	return (node);
}
