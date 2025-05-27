/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:19 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/27 18:56:39 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	parent_process(t_list **pids)
{
	long				pid;
	t_list				*tmp;
	int					status;
	struct sigaction	sa_old;
	int					last_ret;

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
		last_ret = get_exit_status(&status);
		tmp = tmp->next;
	}
	g_last_ret = last_ret;
	free_pids(pids);
	sigaction(SIGINT, &sa_old, NULL);
	start_signals();
}

void	exit_child_process(char **to_ex, char **envc)
{
	free_tab(to_ex);
	free_tab(envc);
	exit(1);
}

void	access_program(char *path, char **to_ex, char **envc)
{
	if (!path || access(path, F_OK | X_OK) != 0)
		return (printf("minishell: %s: command not found\n", to_ex[0]),
			free_tab(to_ex), free_tab(envc), g_last_ret = 127, exit(127));
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		return (printf("minishell: %s: permission denied\n", to_ex[0]),
			free(path), free_tab(to_ex), free_tab(envc), g_last_ret = 126,
			exit(126));
}

void	child_process(char **to_ex, t_list **envl, int (*pipes)[2], int nb_cmds)
{
	char		**envc;
	char		*path;
	t_builtin	builtin;

	start_signals_exec();
	close_pipes(pipes, nb_cmds);
	builtin = get_builtin_by_name(to_ex[0]);
	envc = lst_to_strs(*envl);
	if (!to_ex || !to_ex[0])
		exit_child_process(to_ex, envc);
	if (builtin)
	{
		g_last_ret = builtin(get_string_tab_len(to_ex), to_ex, envl);
		exit(g_last_ret);
	}
	else if (has_absolute_path(to_ex[0]) || has_relative_path(to_ex[0]))
	{
		if (access(to_ex[0], F_OK | X_OK) == 0)
			path = ft_strdup(to_ex[0]);
		else
			return (printf("minishell: %s: command not found\n", to_ex[0]),
				free_tab(to_ex), free_tab(envc), g_last_ret = 127, exit(127));
	}
	else
		path = find_cmd_path(to_ex[0], envc);
	access_program(path, to_ex, envc);
	execve(path, to_ex, envc);
	return (perror("execve"), free(path),
		free_tab(to_ex), free_tab(envc), exit(1));
}
