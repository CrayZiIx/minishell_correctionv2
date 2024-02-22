/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:30:40 by mamottet          #+#    #+#             */
/*   Updated: 2024/02/22 17:40:30 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	simple_put(char *str, int fd)
{
	ft_putstr_fd(str, fd);
}

void	syntax_error(int err_type, char **param, t_glob *g_global)
{
	char	*tmp;

	tmp = NULL;
	if (param && ft_matrixlen(param) == 2)
		tmp = ft_strjoin(ft_strjoin(param[0], ": ", g_global),
				ft_strjoin(param[1], ": ", g_global), g_global);
	else if (param)
		tmp = ft_strjoin(param[0], ": ", g_global);
	simple_put(tmp, 2);
	if (err_type == SYNTAXE_REDIR)
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	else if (err_type == SYNTAXE_PIP)
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	else if (err_type == ARG_ERROR)
		ft_putendl_fd("too many arguments", 2);
}
