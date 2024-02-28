/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:28:57 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/27 18:34:54 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sig_int;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigint_cmd(int sig)
{
	if (sig == SIGINT)
	{
		rl_done = 1;
		g_sig_int = 1;
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
