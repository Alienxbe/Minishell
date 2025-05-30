/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:33:57 by marykman          #+#    #+#             */
/*   Updated: 2025/05/27 19:28:19 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "builtins.h"
#include "exec.h"

int	g_last_ret = 0;

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
		if (!pipes[i])
			exit(1);
		if (pipe(pipes[i]) < 0)
			exit(1);
	}
	return (pipes);
}

static void	exec(t_cmd_table *cmd_table, t_cmd *cmd,
					t_list **envl, int (*pipes)[2])
{
	long	pid;
	t_list	*new_node;
	char	**to_ex;

	to_ex = lst_to_strs(cmd->tokens);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		child_process(to_ex, envl, pipes, cmd_table->cmd_count);
	new_node = ft_lstnew((void *)pid);
	if (!new_node)
		exit(1);
	ft_lstadd_back(&cmd_table->pids, new_node);
	free_tab(to_ex);
}

static void	exec_cmd(t_cmd_table *cmd_table,
					int cmd_index, t_list **envl, int (*pipes)[2])
{
	int		saved_io[2];
	t_cmd	*cmd;

	cmd = cmd_table->cmds->content;
	cmd->cmd_index = cmd_index;
	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	set_pipes_redirs(cmd->redirs, cmd_index, pipes, cmd_table->cmd_count);
	exec(cmd_table, cmd, envl, pipes);
	dup2(saved_io[0], STDIN_FILENO);
	dup2(saved_io[1], STDOUT_FILENO);
	close(saved_io[0]);
	close(saved_io[1]);
}

void	exec_cmds(t_cmd_table *cmd_table, t_list **envl)
{
	int		(*pipes)[2];
	int		i;
	int		nb_cmds;

	if (!cmd_table || !envl)
		return ;
	nb_cmds = cmd_table->cmd_count;
	cmd_table->pids = NULL;
	pipes = init_pipes(nb_cmds);
	i = 0;
	while (i < nb_cmds)
	{
		exec_cmd(cmd_table, i, envl, pipes);
		cmd_table->cmds = cmd_table->cmds->next;
		i++;
	}
	close_pipes(pipes, nb_cmds);
	parent_process(&cmd_table->pids);
}
