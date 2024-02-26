/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <gmallet@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:51 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/26 20:52:01 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_string_redir(char *s, int *i)
{
		if ((s[(*i)] == '>' && s[(*i) + 1] == '>') || (s[(*i)] == '<' && s[(*i) + 1] == '<'))
		{
			(*i) += 2;
			return SYNTAXE_NL;
		}	
		else if (s[*i] == '>' || s[*i] == '<')
		{
			(*i)++;
			return SYNTAXE_R;
		}
		else if (s[*i] == '|')
		{
			(*i)++;
			return SYNTAXE_PIP;
		}
		while (s[*i] && !ft_isspace(s[*i]))
			(*i)++;
		return 0;
}

// SYNTAXE_PIP
// SYNTAX_NIL

int	check_string_redir_tab(char *s)
{
	int i;
	int t;
	int old;

	i = 0;
	old = 0;
	while (s[i] != '\0')
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] == '\0')
			break ;
		t = check_string_redir(s, &i);
		// printf("return from check string %s\n", s[i]);
		if (old && t)
		{
			if (old == truc && && t)
				tamere la pute;	
			return (t);
		}
		old = t;
	}
	return (old);
}
