/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:21:51 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/21 00:11:54 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// extern t_glob	g_global;

static int	ft_count_words(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array(char **aux, t_double_str *dstr,
	int i[3], t_glob *g_global)
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(dstr->s);
	while (dstr->s[i[0]])
	{
		while (ft_strchr(dstr->set, dstr->s[i[0]]) && dstr->s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(dstr->set, dstr->s[i[0]])
				|| q[0] || q[1]) && dstr->s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && dstr->s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && dstr->s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(dstr->s, i[1], i[0] - i[1], &g_global->gc);
	}
	return (aux);
}

int 	check_arg_export(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]) == 1)
		return (printf(" : export: `%s': not a valid identifier\n",str),1);
	i ++;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == ' ')
			return (printf("export: `%c': not a valid identifier \n",str[i - 1]),1);
		if (ft_isalpha(str[i]) == 1 || str[i] == '_' 
			|| ft_isalnum(str[i]) == 1 || str[i])
			i ++;
		else
			return (1);
	}
	if (str[0] == ' ')
		return (1);
	return (0);
}

char	**ft_cmdtrim(char const *s, char *set, t_glob *g_global)
{
	char			**aux;
	int				nwords;
	int				i[3];
	int				counts[2];
	t_double_str	dstr;

	dstr.s = (char *)s;
	dstr.set = set;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words(dstr.s, dstr.set, counts);
	if (nwords == -1)
		return (NULL);
	aux = gc_malloc(&g_global->gc, (nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, &dstr, i, g_global);
	aux[nwords] = NULL;
	return (aux);
}
