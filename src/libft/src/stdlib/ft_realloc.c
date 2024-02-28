/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:35:10 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:35:11 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*res;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	res = malloc(size);
	if (!res)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		ft_memcpy(res, ptr, size);
		free(ptr);
	}
	return (res);
}
