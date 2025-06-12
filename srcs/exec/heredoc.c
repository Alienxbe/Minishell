/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:28:11 by marykman          #+#    #+#             */
/*   Updated: 2025/06/12 17:05:12 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_string.h"
#include "ft_printf.h"
#include "parsing.h"
#include "exec.h"

static void	write_heredoc_fd(void *content, void *param)
{
	char	*str;
	int		*fd;

	str = content;
	fd = param;
	if (!str || !fd)
		return ;
	ft_fprintf(*fd, "%s\n", str);
}

int	open_heredoc(t_redir *redir, int *fd_io)
{
	int	fd_heredoc;

	if (fd_io[0] != -2)
		close(fd_io[0]);
	fd_heredoc = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_io[0] == -1)
		return (1);
	ft_lstiterp(redir->heredoc, write_heredoc_fd, &fd_heredoc);
	close(fd_heredoc);
	free(redir->filename);
	redir->filename = ft_strdup(".heredoc");
	return (open_infile(redir, fd_io));
}
