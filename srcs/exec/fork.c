/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:19 by vpramann          #+#    #+#             */
/*   Updated: 2025/06/02 18:32:18 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "ft_string.h"
#include "ft_printf.h"
#include "env.h"
#include "builtins.h"
#include "exec.h"

int	get_exit_status(int *status)
{
	int		ret;

	if (WIFEXITED(*status))
		ret = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
			write(1, "\n", 1);
		ret = 128 + WTERMSIG(*status);
	}
	return (ret);
}

void	parent_process(t_list *cmds)
{
	t_cmd				*cmd;
	int					status;
	struct sigaction	sa_old;

	sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_IGN}, &sa_old);
	while (cmds)
	{
		cmd = cmds->content;
		if (cmd->pid)
		{
			waitpid(cmd->pid, &status, 0);
			cmd->exit_status = get_exit_status(&status);
		}
		cmds = cmds->next;
	}
	sigaction(SIGINT, &sa_old, NULL);
	start_signals();
}

void	access_cmd(char *path, char **to_ex, char **envc)
{
	if (!path || access(path, F_OK | X_OK) != 0)
		return (ft_printf("minishell: %s: command not found\n", to_ex[0]),
			free_tab(to_ex), free_tab(envc), exit(127));
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		return (ft_printf("minishell: %s: permission denied\n", to_ex[0]),
			free(path), free_tab(to_ex), free_tab(envc), exit(126));
}

char	*access_program(char **to_ex, char **envc)
{
	char	*path;

	if (access(to_ex[0], F_OK | X_OK) == 0)
		path = ft_strdup(to_ex[0]);
	else
		return (ft_printf("minishell: %s: command not found\n", to_ex[0]),
			free_tab(to_ex), free_tab(envc), exit(127), NULL);
	return (path);
}

void	child_process(char **argv, t_cmd_table *cmd_table, t_list **envl)
{
	char		**envc;
	char		*path;

	start_signals_exec();
	close_pipes(cmd_table->pipes, cmd_table->cmd_count);
	envc = lst_to_strs(*envl);
	if (!argv || !argv[0])
		exit_child_process(argv, envc);
	else if (has_absolute_path(argv[0]) || has_relative_path(argv[0]))
		path = access_program(argv, envc);
	else
		path = find_cmd_path(argv[0], envc);
	access_cmd(path, argv, envc);
	execve(path, argv, envc);
	return (perror("execve"), free(path),
		free_tab(argv), free_tab(envc), exit(1));
}
