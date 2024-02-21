/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:44:47 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/20 23:26:36 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

char	*expand_path(char *s, int i, int quotes[2], char *var, t_glob *g_global)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (s && s[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && s[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && s[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && s[i] == '~' && (i == 0 || \
			s[i - 1] != '$'))
		{
			aux = ft_substr(s, 0, i, &g_global->gc);
			path = ft_strjoin(aux, var, &g_global->gc);
			aux = ft_substr(s, i + 1, ft_strlen(s), &g_global->gc);
			s = ft_strjoin(path, aux, &g_global->gc);
			return (expand_path(s, i + ft_strlen(var) - 1, quotes, var, g_global));
		}
	}
	return (s);
}

static char	*get_substr_var(char *s, int i, t_prompt *prompt, t_glob *g_global)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&s[i], "|\"\'$?>< ") + (ft_strchr("$?", s[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(s) - 1;
	aux = ft_substr(s, 0, i - 1, &g_global->gc);
	var = ft_getenv(&s[i], prompt->envp, \
		ft_strchars_i(&s[i], "\"\'$|>< "), g_global);
	if (!var && s[i] == '$')
		var = ft_itoa(prompt->pid, &g_global->gc);
	else if (!var && s[i] == '?')
		var = ft_itoa(g_global->g_state_old, &g_global->gc);
	path = ft_strjoin(aux, var, &g_global->gc);
	aux = ft_strjoin(path, &s[i + pos], &g_global->gc);
	return (aux);
}

char	*expand_vars(char *s, int i, int quotes[2], t_prompt *prompt, t_glob *g_global)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (s && s[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && s[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && s[i] == '\"')) % 2;
		if (!quotes[0] && s[i] == '$' && s[i + 1] && \
			((ft_strchars_i(&s[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&s[i + 1], "/~%^{}:;\"") && quotes[1])))
			return (expand_vars(get_substr_var(s, ++i, prompt, g_global), -1, \
				quotes, prompt, g_global));
	}
	return (s);
}
