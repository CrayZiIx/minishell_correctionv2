/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:35:04 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:35:07 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_len(int n)
{
	int		itoa_len;
	long	nb;

	if (n == 0)
		return (1);
	itoa_len = 0;
	nb = (long)n;
	if (nb < 0)
	{
		itoa_len++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		itoa_len++;
	}
	return (itoa_len);
}

static void	itoa_alt(int n, int len, char *res)
{
	long	nb;
	int		i;

	res[len] = '\0';
	nb = (long)n;
	if (nb < 0)
	{
		nb *= -1;
		res[len - 1] = '-';
	}
	i = -1;
	while (nb > 0)
	{
		res[++i] = nb % 10 + '0';
		nb /= 10;
	}
	ft_strrev(res);
}

char	*ft_itoa(int n, void *gc)
{
	char	*res;
	int		len;

	len = itoa_len(n);
	res = gc_malloc(gc, sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (!n)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	itoa_alt(n, len, res);
	return (res);
}
