/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:36:41 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:41 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	c = (unsigned char)c;
	str = (char *)s;
	i = 0;
	while (str[i])
		i++;
	if ((unsigned char)c == '\0')
		return (&str[i]);
	while (i--)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
	}
	return (NULL);
}
