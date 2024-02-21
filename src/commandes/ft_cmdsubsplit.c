/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsubsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:25:17 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/20 23:33:46 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// extern t_glob	g_global;

static int	ft_count_words(char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array(char **aux,
	t_double_str *dstr, int i[3], t_glob *g_global)
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (dstr->s && dstr->s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(dstr->set, dstr->s[i[0]]))
		{
			while ((!ft_strchr(dstr->set, dstr->s[i[0]]) || q[0] || q[1]) \
				&& dstr->s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && dstr->s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && dstr->s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		aux[i[2]++] = ft_substr(dstr->s, i[1], i[0] - i[1], &g_global->gc);
	}
	return (aux);
}

char	**ft_cmdsubsplit(char const *s, char *set, t_glob *g_global)
{
	char			**aux;
	int				nwords;
	int				i[3];
	t_double_str	dstr;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	dstr.s = (char *)s;
	dstr.set = set;
	if (!s)
		return (NULL);
	nwords = ft_count_words((char *)s, set, 0);
	if (nwords == -1)
		return (NULL);
	aux = gc_malloc(&g_global->gc, (nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, &dstr, i, g_global);
	aux[nwords] = NULL;
	return (aux);
}
