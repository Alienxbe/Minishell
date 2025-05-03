/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:15:50 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/03 12:46:53 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	(*init_pipes(int nb_cmds))[2]
{
	int	(*pipes)[2];
	int	i;

	if (nb_cmds == 1)
		return (0);
	pipes = ft_calloc(nb_cmds, sizeof(int[2]));
	if (!pipes)
		exit(1);
	i = -1;
	while (++i < nb_cmds - 1)
	{
		if(!pipes[i])
			exit(1);
		if (pipe(pipes[i]) < 0)
			exit(1);
	}	
	return (pipes);
}

int is_redir(t_list *redirs, t_redir_type type)
{
	t_redir *redir;

	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == type)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

int open_infile(t_redir *redir)
{
	if (redir->fd_io[0] != -2)
		close (redir->fd_io[0]);
	redir->fd_io[0] = open(redir->filename, O_RDONLY);
	if (redir->fd_io[0] == -1)
	{
		perror(redir->filename);
		exit(1);
	}
	else
	{
		dup2(redir->fd_io[0], STDIN_FILENO);
		close(redir->fd_io[0]);
	}
	return (redir->fd_io[0]);
}

int open_outfile(t_redir *redir)
{
	if (redir->fd_io[1] != -2)
		close (redir->fd_io[1]);	
	if (redir->type == REDIR_STDOUT)
		redir->fd_io[1] = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir->type == REDIR_STDOUT_APPEND)
		redir->fd_io[1] = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd_io[1] == -1)
	{
		perror(redir->filename);
		exit(1);
	}
	else
	{
		dup2(redir->fd_io[1], STDOUT_FILENO);
		close(redir->fd_io[1]);
	}
	return (redir->fd_io[1]);
}

int open_files(t_list *redirs)
{
	t_redir *redir;

	
	
	if (!redirs)
		return (0);
	redir = redirs->content;
	redir->fd_io[0] = -2;
	redir->fd_io[1] = -2;
	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == REDIR_STDIN)
			redir->fd_io[0] = open_infile(redir);
		else if (redir->type == REDIR_STDOUT)
			redir->fd_io[1] = open_outfile(redir);
		else if (redir->type == REDIR_STDOUT_APPEND)
			redir->fd_io[1] = open_outfile(redir);
		if (redir->fd_io[0] == -1 || redir->fd_io[1] == -1)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

void	set_pipes(t_list *redirs, int cmd_index, int (*pipes)[2], int nb_cmds)
{
	
	if (open_files(redirs))
		return ;
	if (!is_redir(redirs, REDIR_STDIN) && cmd_index != 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (!is_redir(redirs, REDIR_STDOUT) && !is_redir(redirs, REDIR_STDOUT_APPEND) && cmd_index != nb_cmds - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
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


void close_files(t_list *redirs)
{
	t_redir *redir;

	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == REDIR_STDIN)
			close(redir->fd_io[0]);
		else if (redir->type == REDIR_STDOUT || redir->type == REDIR_STDOUT_APPEND)
			close(redir->fd_io[1]);
		redirs = redirs->next;
	}
}
