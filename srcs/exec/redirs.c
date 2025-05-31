/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:15:50 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/30 17:57:57 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "exec.h"

int	open_infile(t_redir *redir, int *fd_io)
{
	if (fd_io[0] != -2)
		close (fd_io[0]);
	fd_io[0] = open(redir->filename, O_RDONLY);
	if (fd_io[0] == -1)
	{
		perror(redir->filename);
		exit(1);
	}
	else
	{
		dup2(fd_io[0], STDIN_FILENO);
		close(fd_io[0]);
	}
	return (fd_io[0]);
}

int	open_outfile(t_redir *redir, int *fd_io)
{
	if (fd_io[1] != -2)
		close (fd_io[1]);
	if (redir->type == REDIR_STDOUT)
		fd_io[1] = open(redir->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir->type == REDIR_STDOUT_APPEND)
		fd_io[1] = open(redir->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_io[1] == -1)
	{
		perror(redir->filename);
		exit(1);
	}
	else
	{
		dup2(fd_io[1], STDOUT_FILENO);
		close(fd_io[1]);
	}
	return (fd_io[1]);
}

int	open_files(t_list *redirs)
{
	t_redir	*redir;
	int		fd_io[2];

	if (!redirs)
		return (0);
	redir = redirs->content;
	fd_io[0] = -2;
	fd_io[1] = -2;
	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == REDIR_STDIN)
			open_infile(redir, fd_io);
		else if (redir->type == REDIR_STDOUT
			|| redir->type == REDIR_STDOUT_APPEND)
			open_outfile(redir, fd_io);
		if (fd_io[0] == -1 || fd_io[1] == -1)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

void	set_pipes_redirs(t_list *redirs, int cmd_index,
		int (*pipes)[2], int nb_cmds)
{
	if (open_files(redirs))
		return ;
	if (!is_redir(redirs, REDIR_STDIN) && cmd_index != 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (!is_redir(redirs, REDIR_STDOUT)
		&& !is_redir(redirs, REDIR_STDOUT_APPEND) && cmd_index != nb_cmds - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
}

/*void	close_files(t_list *redirs)
{
	t_redir	*redir;

	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == REDIR_STDIN)
			close(redir->fd_io[0]);
		else if (redir->type == REDIR_STDOUT
			|| redir->type == REDIR_STDOUT_APPEND)
			close(redir->fd_io[1]);
		redirs = redirs->next;
	}
}*/
