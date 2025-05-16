/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:42:20 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/16 18:04:17 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	is_redir(t_list *redirs, t_redir_type type)
{
	t_redir	*redir;

	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == type)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

void	close_pipes(int (*pipes)[2], int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = -1;
	while (++i < pipe_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	free(pipes);
}

void	free_pids(t_list **pids)
{
	t_list	*tmp;

	if (!pids || !*pids)
		return ;
	while (*pids)
	{
		tmp = *pids;
		*pids = (*pids)->next;
		free(tmp);
	}
}
