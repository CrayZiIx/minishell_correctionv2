/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamottet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:30:40 by mamottet          #+#    #+#             */
/*   Updated: 2024/02/22 14:45:47 by mamottet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*syntax_error(int err_type, char *param, int err, t_glob *g_global)
{
	g_global->g_state = err;
	if (err_type == SYNTAXE_REDIR)
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	else if (err_type == SYNTAXE_PIP)
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	else if (err_type == ARG_ERROR)
		ft_putendl_fd("too many arguments", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}
