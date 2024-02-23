/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamottet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:31:26 by mamottet          #+#    #+#             */
/*   Updated: 2024/02/23 10:32:31 by mamottet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_redirc_char(char c)
{
	if (c == '>' || c == '<')
			return (1);
	return (0);
}

int is_redir_like(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_redirc_char(str[i]) == 0)
			return (1);
		i ++;
	}
	return (0);
}
