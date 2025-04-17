/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:15:50 by vpramann          #+#    #+#             */
/*   Updated: 2025/04/17 18:15:54 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	(*init_pipes(t_list *cmds))[2]
{
	int	(*pipes)[2];
	int	pipe_count;
	int	i;

	pipe_count = ft_lstsize(cmds);
	if (pipe_count < 2)
		return (NULL);
	pipes = ft_calloc(pipe_count, sizeof(int[2]));
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < pipe_count - 1)
	{
		if (pipe(pipes[i]) < 0)
		{
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);	// TODO: free
		}
	}	
	return (pipes);
}

void	set_pipes(int cmd_index, int (*pipes)[2], int nb_cmds)
{
	/*t_redir *pot_file;
	t_redir_type red_type;
	int fd;
	
	// if redir_file
	pot_file = redir->content;
	red_type = 0;
	fd = -1;
	if (pot_file->filename)
	{
		if (pot_file->type)
			red_type = pot_file->type;
		if (red_type == REDIR_STDIN)
		{
			if (access(pot_file->filename, F_OK) == 0)
			{
				if (access(pot_file->filename, R_OK) == 0)
					fd = open(pot_file->filename, O_RDONLY, 0444);
			else
				print_errors(3, NULL, file1);
			}
			if (fd == -1)
				exit (1);
			dup2(fd, STDIN_FILENO);
			dup2(pipes[0][1], STDOUT_FILENO);	
		}
		else if (red_type == REDIR_STDOUT)
		{
			
		}
	}*/
	// else redir pipe
	if (cmd_index != 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index != nb_cmds - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	
}

