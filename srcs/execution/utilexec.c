/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:36:02 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/29 19:19:28 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_parse(void)
{
	t_parse	*lst;
	int		i;

	i = 0;
	lst = g_global.parse;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	cmdin_parse(t_parse *parse)
{
	t_parse	*lst;

	lst = parse;
	while (lst)
	{
		if (lst->cmd == NULL || !lst->cmd)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	exec_cmdmulti(t_parse *parse, t_list *alst, t_exp *atc, char **lab)
{
	if (!ft_strcmp(tolower2(parse->cmd), "exit"))
		ft_exit(parse->arg);
	else if (!ft_strcmp(tolower2(parse->cmd), "env"))
		print_list(alst);
	else if (!ft_strcmp(tolower2(parse->cmd), "echo"))
		ft_echo(parse);
	else if (!ft_strcmp(tolower2(parse->cmd), "pwd"))
		printf("%s\n", getcwd(NULL, 0));
	else if (!ft_strncmp(parse->cmd, "cd", 2))
		cd(parse, alst);
	else if (!ft_strcmp(parse->cmd, "unset"))
		unset(&alst, &atc);
	else if (!ft_strcmp(parse->cmd, "export"))
		port(atc, alst);
	else
	{
		if (execve(check_path_access(alst, parse->cmd),
				lab, enov(alst)) == -1)
		{
			if (!ft_strncmp(parse->cmd, "/bin/", 2))
				printf("%s: No such file or directory\n", parse->cmd);
			else
				printf("%s: command not found\n", parse->cmd);
		}
	}
}

void	execlab(t_parse *elem, t_list *alst, t_exp *atc)
{
	char	**lab;

	lab = NULL;
	lab = check_elem(elem, alst, lab);
	if (lab[0] == NULL)
	{
		init_signals();
		return ;
	}
	if (len_parse() == 1)
		exec_cmd(elem, alst, atc, lab);
	else
	{
		exec_cmdmulti(elem, alst, atc, lab);
		free_tab(lab);
		exit(0);
	}
	free_tab(lab);
}
