/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 21:29:43 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/19 23:07:05 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern t_glob	g_global;

void sig(int sig)
{
	if (sig == SIGINT)
		g_global.sig_int = 1;
}

char	*get_here_str(char *s[2], size_t len, char *limit, char *warn)
{
	char				*temp;
	struct sigaction	action;
	
	g_global.sig_int = 0;
	// signal(SIGINT, handle_sigint_cmd);
	action.sa_handler = sig;
	sigemptyset(&action.sa_mask);
	sigaction(SIGINT, &action, NULL);
	action.sa_flags = 0;
	while (g_global.g_state != 130 && (!s[0] || ft_strncmp(s[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		temp = s[1];
		s[1] = ft_strjoin(s[1], s[0], &g_global.gc);
		ft_putstr_fd("> ", STDOUT_FILENO);
		s[0] = get_next_line(STDIN_FILENO);
		if (g_global.sig_int)
			break ;
		if (!s[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = s[0];
		s[0] = ft_strjoin(s[0], "\n", &g_global.gc);
		len = ft_strlen(s[0]) - 1;
	}
	signal(SIGINT, handle_sigint_cmd);
	return (s[1]);
}

int	get_here_doc(char *s[2], char *aux[2])
{
	int		fd[2];

	g_global.g_state = 0;
	if (pipe(fd) == -1)
	{
		ft_perror(PIPE_ERR, NULL, 1);
		return (-1);
	}
	s[1] = get_here_str(s, 0, aux[0], aux[1]);
	if (s[1] == NULL)
	{
		printf("tesfd\n");
	}
	write(fd[WRITE_END], s[1], ft_strlen(s[1]));
	close(fd[WRITE_END]);
	if (g_global.g_state == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
