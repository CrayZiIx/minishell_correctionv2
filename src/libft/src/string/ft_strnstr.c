/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:36:37 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:38 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	if (!little[0])
		return ((char *)big);
	if (!len)
		return (NULL);
	i = 0;
	little_len = ft_strlen(little);
	while (big[i] && i + little_len <= len)
	{
		if (!ft_strncmp(&big[i], little, little_len))
			return (&((char *)big)[i]);
		i++;
	}
	return (0);
}
