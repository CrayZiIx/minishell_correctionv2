/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:36:44 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:44 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	tmp;

	if (str)
	{
		len = ft_strlen(str);
		i = -1;
		j = len - 1;
		while (++i < len / 2)
		{
			tmp = str[i];
			str[i] = str[j];
			str[j] = tmp;
			j--;
		}
	}
	return (str);
}
