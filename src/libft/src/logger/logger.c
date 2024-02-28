/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:33:51 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:33:52 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger_internal.h"
#include "libft.h"
#include "../stdio/ft_printf_internal.h"

void	logger_track(char *file, int line)
{
	ft_printf("  --> %s:%d\n", file, line);
}

static void	logger_print_level(int level)
{
	if (level == LOGGER_DEBG)
		ft_printf(ANSI_BWHT "[DEBG]" ANSI_RESET " ");
	else if (level == LOGGER_INFO)
		ft_printf(ANSI_BBLU "[INFO]" ANSI_RESET " ");
	else if (level == LOGGER_WARN)
		ft_printf(ANSI_BYEL "[WARN]" ANSI_RESET " ");
	else if (level == LOGGER_ERRO)
		ft_printf(ANSI_BRED "[CRIT]" ANSI_RESET " ");
	else if (level == LOGGER_CRIT)
		ft_printf(ANSI_BMAG "[CRIT]" ANSI_RESET " ");
}

void	logger(int level, const char *fmt, ...)
{
	va_list		pa;
	const char	*p;

	logger_print_level(level);
	va_start(pa, fmt);
	p = fmt;
	while (*p)
	{
		if (*p != '%')
			ft_putchar_fd(*p, 1);
		else
		{
			p++;
			ft_printf_fmt(*p, pa);
		}
		p++;
	}
	va_end(pa);
	ft_putchar_fd('\n', 1);
}
