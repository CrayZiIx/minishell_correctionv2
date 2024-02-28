/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:31:51 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/27 16:42:26 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_token(char *s, int *t)
{
	if (s)
	{
		if ((s[0] == '>' && s[1] == '>') \
			|| (s[0] == '<' && s[1] == '<'))
			(*t) = SYNTAXE_DR;
		else if ((s[0] == '>' || s[0] == '<' \
			|| s[0] == '|'))
		{
			if (s[0] == '|')
				(*t) = SYNTAXE_PIP;
			(*t) = SYNTAXE_R;
		}
		else
			(*t) = 0;
	}
}

int	check_token_redir(char **s, t_glob *g_global)
{
	int	old_token;
	int	new_token;
	int	i;

	old_token = 0;
	new_token = 0;
	i = 0;
	if (!old_token)
		get_token(s[0], &old_token);
	while (s && s[i] && i < ft_matrixlen(s))
	{
		if (i < 2 && s[i + 1])
		{
			i++;
			get_token(s[i], &new_token);
		}
		else
			break ;
		if ((old_token && new_token) && (old_token != SYNTAXE_PIP && new_token != SYNTAXE_PIP))
			return (syntax_error(new_token,NULL, g_global), new_token);
		else
			old_token = new_token;
	}
	return (0);
}

int	check_string_get_token(char *s)
{
	int	i;
	int	old_token;
	int	new_token;

	i = 0;
	old_token = 0;
	while (i <= (int)ft_strlen(s) && s[i] != '\0')
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			if (s[i] == '|')
				new_token = SYNTAXE_PIP;
			else if (s[i] == '>' || s[i] == '<')
				new_token = SYNTAXE_R;
			else if (s[++i] != '\0' && (s[i] == '>' || s[i] == '<'))
				new_token = SYNTAXE_DR;
		}
		else
			new_token = 0;
		i++;
		if ((old_token == SYNTAXE_PIP && new_token == SYNTAXE_PIP))
			return (new_token);
	}
	return (new_token);
}

int	check_string_redir(char **s, t_glob *g_global)
{
	int	string_token;
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i])
			string_token = check_string_get_token(s[i]);
		i++;
		if (string_token && (i == (ft_matrixlen(s))))
		{
			syntax_error(PARS_ERROR,s,g_global);
			return (string_token);
		}
	}
	return (0);
}
