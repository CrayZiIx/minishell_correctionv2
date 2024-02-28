/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:36:47 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:48 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delim(char c, const char *delim)
{
	int	i;

	i = -1;
	while (delim[++i])
	{
		if (c == delim[i])
			return (1);
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*token = NULL;
	char		*start;

	if (str)
		token = str;
	if (!token)
		return (NULL);
	while (*token && is_delim(*token, delim))
		token++;
	if (*token == '\0')
	{
		token = NULL;
		return (NULL);
	}
	start = token;
	while (*token && !is_delim(*token, delim))
		token++;
	if (*token)
	{
		*token = '\0';
		token++;
	}
	return (start);
}
