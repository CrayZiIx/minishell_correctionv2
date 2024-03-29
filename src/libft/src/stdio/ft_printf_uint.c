/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:34:08 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:34:09 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

static int	uitoa_len(unsigned int n)
{
	unsigned long	nb;
	int				uitoa_len;

	if (n == 0)
		return (1);
	uitoa_len = 0;
	nb = (unsigned long)n;
	while (nb > 0)
	{
		nb /= 10;
		uitoa_len++;
	}
	return (uitoa_len);
}

static void	uitoa_alt(unsigned int n, int len, char *res)
{
	unsigned long	nb;
	int				i;

	res[len] = '\0';
	nb = (unsigned long)n;
	i = -1;
	while (nb > 0)
	{
		res[++i] = nb % 10 + '0';
		nb /= 10;
	}
	ft_strrev(res);
}

static char	*uitoa(unsigned int n)
{
	char	*res;
	int		len;

	len = uitoa_len(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (!n)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	uitoa_alt(n, len, res);
	return (res);
}

int	ft_printf_uint(unsigned int nbr)
{
	char	*n;
	int		printed;

	n = uitoa(nbr);
	if (!n)
		return (0);
	printed = ft_printf_str(n);
	free(n);
	return (printed);
}
