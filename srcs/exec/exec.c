/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:33:57 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 19:10:55 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_memory.h"
#include "env.h"
#include "builtins.h"
#include "exec.h"

void	exit_child_process(char **to_ex, char **envc)
{
	free_tab(to_ex);
	free_tab(envc);
	exit(1);
}

int	(*init_pipes(int nb_cmds))[2]
{
	int	(*pipes)[2];
	int	i;

	if (nb_cmds == 1)
		return (0);
	pipes = ft_calloc(nb_cmds, sizeof(int [2]));
	if (!pipes)
		exit(1);
	i = -1;
	while (++i < nb_cmds - 1)
	{
		if (pipe(pipes[i]) < 0)
			exit(1);
	}
	return (pipes);
}

static void	exec(t_cmd *cmd, t_msh *msh)
{
	char		**argv;
	t_builtin	f_builtin;

	argv = lst_to_strs(cmd->tokens);
	if (!argv)
		return ;
	f_builtin = get_builtin_by_name(argv[0]);
	if (f_builtin)
		cmd->exit_status = f_builtin(ft_lstsize(cmd->tokens), argv, msh);
	else
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			exit(1);
		else if (cmd->pid == 0)
			child_process(argv, &msh->cmd_table, &msh->envl);
	}
	free_tab(argv);
}

static void	exec_cmd(t_cmd *cmd, t_msh *msh)
{
	int			saved_io[2];

	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	set_pipes_redirs(cmd, &msh->cmd_table);
	exec(cmd, msh);
	dup2(saved_io[0], STDIN_FILENO);
	dup2(saved_io[1], STDOUT_FILENO);
	close(saved_io[0]);
	close(saved_io[1]);
}

void	exec_cmds(t_msh *msh)
{
	t_list	*cmd;

	msh->cmd_table.pipes = init_pipes(msh->cmd_table.cmd_count);
	cmd = msh->cmd_table.cmds;
	while (cmd)
	{
		exec_cmd(cmd->content, msh);
		cmd = cmd->next;
	}
	close_pipes(msh->cmd_table.pipes, msh->cmd_table.cmd_count);
	parent_process(msh->cmd_table.cmds);
}
