/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:15:50 by vpramann          #+#    #+#             */
/*   Updated: 2025/06/12 17:05:01 by marykman         ###   ########.fr       */
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
		return (1);
	else
	{
		dup2(fd_io[0], STDIN_FILENO);
		close(fd_io[0]);
	}
	return (0);
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
		return (1);
	else
	{
		dup2(fd_io[1], STDOUT_FILENO);
		close(fd_io[1]);
	}
	return (0);
}

int	open_files(t_list *redirs)
{
	t_redir	*redir;
	int		fd_io[2];
	int		ret;

	if (!redirs)
		return (0);
	redir = redirs->content;
	fd_io[0] = -2;
	fd_io[1] = -2;
	ret = 0;
	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == REDIR_STDIN)
			ret = open_infile(redir, fd_io);
		else if (redir->type == REDIR_STDOUT
			|| redir->type == REDIR_STDOUT_APPEND)
			ret = open_outfile(redir, fd_io);
		else if (redir->type == REDIR_HEREDOC)
			ret = open_heredoc(redir, fd_io);
		if (ret || fd_io[0] == -1 || fd_io[1] == -1)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

int	set_pipes_redirs(t_cmd *cmd, t_cmd_table *cmd_table)
{
	if (open_files(cmd->redirs))
		return (1);
	if (!is_redir(cmd->redirs, REDIR_STDIN)
		&& !is_redir(cmd->redirs, REDIR_HEREDOC) && cmd->index != 0)
		dup2(cmd_table->pipes[cmd->index - 1][0], STDIN_FILENO);
	if (!is_redir(cmd->redirs, REDIR_STDOUT)
		&& !is_redir(cmd->redirs, REDIR_STDOUT_APPEND)
		&& cmd->index != cmd_table->cmd_count - 1)
		dup2(cmd_table->pipes[cmd->index][1], STDOUT_FILENO);
	return (0);
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
