/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:16:19 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/03 16:38:25 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	parent_process(t_list **pids)
{
	long	pid;
	t_list	*tmp;

	if (!pids || !*pids)
		return ;
	tmp = *pids;
	while (tmp)
	{
		if (!tmp->content)
			return ;
		pid = *(long *)(tmp);
		waitpid(pid, NULL, 0);
		tmp = tmp->next;
	}
}

void	child_process(t_cmd *cmd, char **envc, int (*pipes)[2], int nb_cmds)
{
	char	**to_ex;
	char	*path;

	close_pipes(pipes, nb_cmds);
	to_ex = lst_to_strs(cmd->tokens);
	if (!to_ex || !to_ex[0])
		return ;
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
	if (execve(path, to_ex, envc) == -1)
		return (perror("execve"), free(path),
			free_tab(to_ex), free_tab(envc), exit(1));
	free(path);
	free_tab(to_ex);
	free_tab(envc);
	exit(0);
}

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
