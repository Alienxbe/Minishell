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

#include "exec.h"

static void exec(t_cmd *cmd, char **envl)
{
	char	**to_ex;
	char	*path;
	int		pid;
	
	//if (isbuiltin(tcmd))
	// ftbuiltin
	to_ex = lst_to_strs(cmd->tokens);
	if (!to_ex || !to_ex[0])
	{
		free_tab(to_ex);
		return ;
	}
	path = find_cmd_path(to_ex[0], envl);
	pid = fork();
	if (pid == -1)
	{
		free(path);
		free_tab(to_ex);
		free_tab(envl);
		return ;
	}
	if (pid == 0)
	{
		if (execve(path, to_ex, envl) == -1)
		{
			free(path);
			free_tab(to_ex);
			free_tab(envl);
			exit(1);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

static void	exec_cmd(t_cmd *cmd,int cmd_index, t_list *envl, int nb_cmds)
{
	int	saved_io[2];
	char	**envc;

	
	(void)envl;
	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	envc = lst_to_strs(envl);
	// Setup pipes (redirect or pipe) -> set stdin/out
	set_pipes(cmd_index, &saved_io, nb_cmds);
	// Exec (builtins or not)
	exec(cmd, envc);
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
	// Loop exec
	lst = cmds;
	i = 0;
	while (lst)
	{
		exec_cmd(lst->content, i++, envl, nb_cmds);
		lst = lst->next;
	}
	free(pipes);
}