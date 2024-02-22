/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:02:33 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/22 15:08:08 by mamottet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// extern t_glob	g_global;

char	*ft_getenv(char *var, char **envp, int n, t_glob *g_global)
{
	char	*s;
	int		i;
	int		n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
		{
			s = ft_substr(envp[i], n2 + 1, ft_strlen(envp[i]), &g_global->gc);
			return (s);
		}
		i++;
	}
	return (NULL);
}

char	**ft_setenv(char *var, char *value, char **envp, t_glob *g_global)
{
	int		i[2];
	char	*aux[2];
	int		n;

	n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=", &g_global->gc);
	aux[1] = ft_strjoin(aux[0], value, &g_global->gc);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			return (envp);
		}
	}
	envp = ft_extend_matrix(envp, aux[1], g_global);
	return (envp);
}

int	var_in_envp(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

