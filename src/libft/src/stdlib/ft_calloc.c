/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:35:01 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:35:01 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size, void *gc)
{
	void	*res;
	size_t	i;

	if (((nmemb > 65535 || size > 65535)) && (size_t)-1 / nmemb < size)
		return (NULL);
	res = gc_malloc(gc, sizeof(char) * size * nmemb);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		((char *)res)[i] = '\0';
		i++;
	}
	return (res);
}
