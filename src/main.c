/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:12:49 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/21 14:02:57 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int	g_sig_int;

/*DESCRPTION*/
static void	ft_getpid(t_prompt *prompt, t_glob *g_global)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_perror(FORK_ERR, NULL, 1, g_global);
		ft_free_matrix(&prompt->envp);
		exit(1);
	}
	if (!pid)
	{
		gc_clean(&g_global->gc);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	prompt->pid = pid - 1;
}

static t_prompt	init_var(t_prompt prompt, char *s,
	char **argv, t_glob *g_global)
{
	char	*num;

	s = getcwd(NULL, 0);
	prompt.envp = ft_setenv("PWD", s, prompt.envp, g_global);
	free(s);
	s = ft_getenv("SHLVL", prompt.envp, 5, g_global);
	if (!s || ft_atoi(s) <= 0)
		num = ft_strdup("1", &g_global->gc);
	else
		num = ft_itoa(ft_atoi(s) + 1, &g_global->gc);
	prompt.envp = ft_setenv("SHLVL", num, prompt.envp, g_global);
	s = ft_getenv("PATH", prompt.envp, 1, g_global);
	s = ft_getenv("_", prompt.envp, 1, g_global);
	if (!s)
		prompt.envp = ft_setenv("_", argv[0], prompt.envp, g_global);
	return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp, t_glob *g_global)
{
	t_prompt	prompt;
	char		*s;

	s = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp, g_global);
	g_global->g_state_old = 0;
	g_global->g_state = 0;
	ft_getpid(&prompt, g_global);
	prompt = init_var(prompt, s, argv, g_global);
	return (prompt);
}

int	main(int ac, char **av, char **envp)
{
	char		*out;
	t_prompt	prompt;
	t_glob		g_global;

	gc_init(&g_global.gc);
	prompt = init_prompt(av, envp, &g_global);
	while (ac)
	{
		g_global.g_state_old = g_global.g_state;
		g_sig_int = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		out = readline("guest@minishell $ ");
		signal(SIGINT, handle_sigint_cmd);
		if (!check_args(out, &prompt, &g_global))
			break ;
		if (g_sig_int)
			g_global.g_state = 130;
		else if (WIFEXITED(g_global.g_state))
			g_global.g_state = WEXITSTATUS(g_global.g_state);
		free(out);
	}
	rl_clear_history();
	gc_clean(&g_global.gc);
	exit(g_global.g_state);
}
