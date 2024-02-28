/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:34:01 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:34:02 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>

int	ft_printf_fmt(char fmt, va_list pa);
int	ft_printf_int(int nbr);
int	ft_printf_str(char *str);
int	ft_printf_str(char *str);
int	ft_printf_uint(unsigned int nbr);
int	ft_printf_ptr(void *ptr);
int	ft_printf_hex(unsigned int nbr, char fmt);

#endif