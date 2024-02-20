/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:56:11 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/19 19:29:30 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// extern t_glob	g_global;

int	ft_countchar(char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

int	ft_strchars_i(const char *s, char *set)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	*my_ptr(void *init_ptr)
{
	static void	*ptr;

	if (init_ptr)
		ptr = init_ptr;
	return (ptr);
}

void	print_error_heredoc(char c, int *i, t_glob *g_global)
{
	if (c == '<')
		ft_putendl_fd(TOKEN_EP_L, 2);
	else if (c == '>')
		ft_putendl_fd(TOKEN_EP_R, 2);
	else
		ft_putendl_fd(TOKEN_ERR_NL, 2);
	g_global->g_state = 2;
	(*i) = -2;
}
