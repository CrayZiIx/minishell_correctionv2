/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:34:04 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:34:05 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"
#include <inttypes.h>

static void	ft_putptr_fd(uintptr_t ptr, int fd)
{
	if (ptr > 15)
		ft_putptr_fd(ptr / 16, fd);
	if (ptr % 16 > 9)
		ft_putchar_fd(ptr % 16 - 10 + 'a', fd);
	else
		ft_putchar_fd(ptr % 16 + '0', fd);
}

int	ft_printf_ptr(void *ptr)
{
	uintptr_t	p;
	int			printed;

	printed = 0;
	p = (uintptr_t)ptr;
	if (ptr)
	{
		printed += write(1, "0x", 2);
		ft_putptr_fd((uintptr_t)ptr, 1);
		while (p)
		{
			p /= 16;
			printed++;
		}
	}
	else
		printed += ft_printf_str("(nil)");
	return (printed);
}
