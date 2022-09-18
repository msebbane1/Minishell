/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:45:22 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/09/18 17:10:38 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	killhere(void)
{
	t_parse	*tete;

	tete = g_global.parse;
	while (tete)
	{
		if (tete->fd_kill > 0)
		{
			close(tete->fd_kill);
		}
		tete = tete->next;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != '\0')
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(void)
{
	t_parse *tete;
	tete = g_global.parse;
	killhere();
	while (tete)
	{
		free_tab(tete->arg);
		free(tete->cmd);
		free(tete->flag);
		tete = tete->next;
	}
}