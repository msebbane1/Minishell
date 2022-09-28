/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbally <lbally@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:03:27 by msebbane          #+#    #+#             */
/*   Updated: 2022/09/28 21:59:24 by lbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

struct s_global	g_global;

char	*rl_gets(void)
{
	static char	*line_read;
	char		*res;

	if (line_read)
	{
		free (line_read);
		line_read = (char *) NULL;
	}
	line_read = readline ("minishell>> ");
	if (line_read && *line_read)
	{
		res = ft_strtrim(line_read, " \t\v\f\r");
		if (ft_strlen(res) > 0)
			add_history(res);
		free(res);
	}
	return (line_read);
}

char	*line_prompt(char *line, char **argv, int argc)
{
	(void)argc;
	(void)argv;
	if (!line)
	{
		signal_exit();
	}
	return (line);
}

void	init_global(char **envp)
{
	g_global.parse = malloc(sizeof(t_parse));
	g_global.env = envp;
	g_global.indice = malloc(sizeof(int) * 1);
	g_global.indice[0] = 0;
	g_global.here = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_exp	*atc;
	t_list	*alst;

	alst = NULL;
	g_global.old_stdin = dup(STDIN_FILENO);
	g_global.old_stdout = dup(STDOUT_FILENO);
	insert_env(envp, &alst);
	insert_exp(envp, &atc);
	while (1)
	{
		init_signals();
		line = rl_gets();
		line = line_prompt(line, av, ac);
		init_global(envp);
		lexer(line);
		remplace(g_global.parse, atc);
		brain(alst, atc);
		free_all();
	}
}
