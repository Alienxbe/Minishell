/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:33:57 by marykman          #+#    #+#             */
/*   Updated: 2025/04/26 20:45:06 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static void exec(t_cmd *cmd, t_list *envl)
{
	char	**to_ex;
	char	**envc;
	char	*path;
	int		pid;
	t_builtin	builtin;
	
	to_ex = lst_to_strs(cmd->tokens);
	if (!to_ex || !to_ex[0])
	{
		free_tab(to_ex);
		return ;
	}
	builtin = get_builtin_by_name(to_ex[0]);
	if (builtin)
		builtin(to_ex, envl);
	else
	{
		envc = lst_to_strs(envl);
		path = find_cmd_path(to_ex[0], envc);
		pid = fork();
		if (pid == -1)
		{
			free(path);
			free_tab(to_ex);
			free_tab(envc);
			return ;
		}
		if (pid == 0)
		{
			if (execve(path, to_ex, envc) == -1)
			{
				free(path);
				free_tab(to_ex);
				free_tab(envc);
				exit(1);
			}
		}
		else
			waitpid(pid, NULL, 0);
	}
	free_tab(to_ex);
}

static void	exec_cmd(t_cmd *cmd,int cmd_index, t_list *envl, int nb_cmds)
{
	int	saved_io[2];

	
	(void)envl;
	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	// Setup pipes (redirect or pipe) -> set stdin/out
	set_pipes(cmd->redirs, cmd_index, &saved_io, nb_cmds);
	// Exec (builtins or not)
	exec(cmd, envl);
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
	int 	nb_cmds;

	(void)envl;
	nb_cmds = ft_lstsize(cmds);
	pipes = init_pipes(cmds);
	lst = cmds;
	i = 0;
	while (lst)
	{
		exec_cmd(lst->content, i++, envl, nb_cmds);
		lst = lst->next;
	}
	close_pipes(pipes, nb_cmds);
}