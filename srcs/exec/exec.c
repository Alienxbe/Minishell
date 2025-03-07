/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:33:57 by marykman          #+#    #+#             */
/*   Updated: 2025/03/07 00:13:53 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_memory.h"
#include "parsing.h"
#include "exec.h"

static int	(*init_pipes(t_list *cmds))[2]
{
	int	(*pipes)[2];
	int	pipe_count;
	int	i;

	pipe_count = ft_lstsize(cmds);
	if (pipe_count < 2)
		return (NULL);
	pipes = ft_calloc(pipe_count - 1, sizeof(pipes));
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < pipe_count - 1)
		if (pipe(pipes[i]) < 0)
			return (NULL);	// TODO: free
	return (pipes);
}

static void	set_pipes(t_list *redir, int cmd_index, int (*pipes)[2])
{
	// if redir_file
	// else redir pipe
	if (cmd_index != 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index)
	dup2(pipes[cmd_index][1], STDOUT_FILENO);
}

static void	exec_cmd(t_cmd *cmd, t_list *cmds,int cmd_index)
{
	int	saved_io[2];

	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	// Setup pipes (redirect or pipe) -> set stdin/out
	set_pipes();
	// Exec (builtins or not)
	dup2(saved_io[0], STDIN_FILENO);
	dup2(saved_io[1], STDOUT_FILENO);
	close(saved_io[0]);
	close(saved_io[1]);
}

void	exec_cmds(t_list *cmds, t_list *envl)
{
	t_list	*lst;
	int		(*pipes)[2];
	int		i;

	(void)envl;
	pipes = init_pipes(cmds);
	// Loop exec
	lst = cmds;
	i = 0;
	while (lst)
	{
		exec_cmd(lst->content, cmds, i++);
		lst = lst->next;
	}
	free(pipes);
}
