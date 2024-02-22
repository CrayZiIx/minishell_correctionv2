/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:02:54 by mamottet          #+#    #+#             */
/*   Updated: 2024/02/22 15:54:12 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	whath_is(char ***a, int *i)
{
	if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] != '<'
		&& a[0][*i + 1][0] != '>')
		return (1);
	else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] != '>'
		&& a[0][*i + 1][0] != '<' )
		return (2);
	else if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
		return (3);
	else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
		a[0][*i + 1][0] == '<')
		return (4);
	else if (a[0][*i][0] != '|')
		return (5);
	else
		return (0);
}

void	ft_close(int fd)
{
	if (fd != -1)
		close(fd);
}

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

void	ft_strnull(char **tab, size_t n)
{
	size_t i = 0;
	while (i != n)
	{
		tab[i] = NULL;
		i++;
	}
}

