/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:51 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/26 17:31:41 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_string_redir2(char *s, int *i, int *t)
{
		if ((s[(*i)] == '>' && s[(*i) + 1] == '>') 
			|| (s[(*i)] == '<' && s[(*i) + 1] == '<'))
		{
			printf("s = [%s]\n", s);
			(*i) += 2;
			(*t) = SYNTAXE_NL;
		}
		else if (*t == 0 && (s[(*i)] == '>' || s[(*i)] == '<' 
			|| s[(*i)] == '|'))
		{
			printf("s2 = [%s]\n", s);
			(*i) += 1;
			if (s[(*i)] == '|')
				(*t) = SYNTAXE_PIP;
			(*t) = SYNTAXE_NL;
		}
		else
			if (*t && s[(*i)++] != ' ')
				(*t) = 0;
		return ((*t));
}

int	check_string_redir(char *s)
{
	int i;
	int t;

	i = 0;
	t = 0;
	if (s[0] == '|')
		return (SYNTAXE_PIP);
	while (s[i] != '\0')
	{
		printf("t = %d\n", t);
		if (s[i] == '<' && s[i + 1] == '>')
			return (0);
		if (check_string_redir2(s, &i, &t))
		{
			printf("t = %d\n", t);
			continue ;
		}
		if (t)
			return (t);
	}
	return (0);
}

int	check_string_redir_tab(char **s, t_glob *g_global)
{
	int i;
	int t;

	i = 0;
	while (s && s[i] && i <= 15)
	{
		t = check_string_redir(s[i]);
		if (t)
			return (syntax_error(t, s, g_global), 1);
		i++;
		t = 0;
	}
	return (0);
}