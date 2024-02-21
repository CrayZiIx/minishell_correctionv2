/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 04:44:47 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/21 02:48:31 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

char	*expand_path(t_double_str *dstr, int i, int quotes[2],
	t_glob *g_global, char *stest)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (dstr->s && dstr->s[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && dstr->s[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && dstr->s[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && dstr->s[i] == '~' && (i == 0 || \
			dstr->s[i - 1] != '$'))
		{
			aux = ft_substr(dstr->s, 0, i, &g_global->gc);
			path = ft_strjoin(aux, stest, &g_global->gc);
			aux = ft_substr(dstr->s, i + 1, ft_strlen(dstr->s), &g_global->gc);
			dstr->s = ft_strjoin(path, aux, &g_global->gc);
			return (expand_path(dstr,
					i + ft_strlen(stest) - 2, quotes, g_global, stest));
		}
	}
	return (dstr->s);
}

static char	*get_substr_var(char *s, int i, t_pt *pt)
{
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&s[i], "|\"\'$?>< ") + (ft_strchr("$?", s[i]) != 0);
	if (pos == -1)
		pos = ft_strlen(s) - 1;
	aux = ft_substr(s, 0, i - 1, &pt->g_global->gc);
	var = ft_getenv(&s[i], pt->prompt->envp, \
		ft_strchars_i(&s[i], "\"\'$|>< "), pt->g_global);
	if (!var && s[i] == '$')
		var = ft_itoa(pt->prompt->pid, &pt->g_global->gc);
	else if (!var && s[i] == '?')
		var = ft_itoa(pt->g_global->g_state_old, &pt->g_global->gc);
	path = ft_strjoin(aux, var, &pt->g_global->gc);
	aux = ft_strjoin(path, &s[i + pos], &pt->g_global->gc);
	return (aux);
}

char	*expand_vars(char *s, int i, int quotes[2], t_pt *pt)
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
			{
				return (expand_vars(get_substr_var(s, ++i, pt), -1, quotes, pt));
			}
	}
	return (s);
}
