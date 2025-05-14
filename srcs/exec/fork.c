/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:19 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/14 16:47:03 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_process(t_list **pids)
{
	long				pid;
	t_list				*tmp;
	int					status;
	struct sigaction	sa_old;

	sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_IGN}, &sa_old);
	if (!pids || !*pids)
		return ;
	tmp = *pids;
	while (tmp)
	{
		if (!tmp->content)
			return ;
		pid = *(long *)(tmp);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		tmp = tmp->next;
	}
	sigaction(SIGINT, &sa_old, NULL);
	start_signals();
}

/*void	child_process(t_cmd *cmd, char **envc, int (*pipes)[2], int nb_cmds)
{
	char	**to_ex;
	char	*path;

	start_signals_exec();
    (void)pipes;
    (void)nb_cmds;
	
	close_pipes(pipes, nb_cmds);
	to_ex = lst_to_strs(cmd->tokens);
	if (!to_ex || !to_ex[0])
	{
		free_tab(to_ex);
        free_tab(envc);
        exit(1);
	}
	if (has_absolute_path(to_ex[0]) || has_relative_path(to_ex[0]))
	{
		if (access(to_ex[0], F_OK | X_OK) == 0)
			path = ft_strdup(to_ex[0]);
		else
			return (printf("minishell: %s: command not found\n", to_ex[0]),
				free_tab(to_ex), free_tab(envc), exit(127));
	}
	else
		path = find_cmd_path(to_ex[0], envc);
	if (!path || access(path, F_OK | X_OK) != 0)
		return (printf("minishell: %s: command not found\n", to_ex[0]),
			free_tab(to_ex), free_tab(envc), exit(127));
	if (execve(path, to_ex, envc) == -1)
		return (perror("execve"), free(path),
			free_tab(to_ex), free_tab(envc), exit(1));
	free(path);
	free_tab(to_ex);
	free_tab(envc);
	exit(0);
}*/

void	child_process(t_cmd *cmd, char **envc, int (*pipes)[2], int nb_cmds)
{
	char	**to_ex;
	char	*path;

	start_signals_exec();
	close_pipes(pipes, nb_cmds);
	to_ex = lst_to_strs(cmd->tokens);
	if (!to_ex || !to_ex[0])
		exit_child_process(to_ex, envc);
	if (has_absolute_path(to_ex[0]) || has_relative_path(to_ex[0]))
	{
		if (access(to_ex[0], F_OK | X_OK) == 0)
			path = ft_strdup(to_ex[0]);
		else
			return (printf("minishell: %s: command not found\n", to_ex[0]),
				free_tab(to_ex), free_tab(envc), exit(127));
	}
	else
		path = find_cmd_path(to_ex[0], envc);
	if (!path || access(path, F_OK | X_OK) != 0)
		return (printf("minishell: %s: command not found\n", to_ex[0]),
			free_tab(to_ex), free_tab(envc), exit(127));
	execve(path, to_ex, envc);
	return (perror("execve"), free(path),
		free_tab(to_ex), free_tab(envc), exit(1));
}

void	exit_child_process(char **to_ex, char **envc)
{
	free_tab(to_ex);
	free_tab(envc);
	exit(1);
}
