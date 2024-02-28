/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:36:54 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:55 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set, void *gc)
{
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	i = 0;
	while (in_set(s1[i], set))
		i++;
	if (i == ft_strlen(s1))
		return (ft_memset(malloc(sizeof(char)), 0, 1));
	j = ft_strlen(s1) - 1;
	while (in_set(s1[j], set))
		j--;
	return (ft_substr(s1, i, j - i + 1, gc));
}
