/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:34:21 by marykman          #+#    #+#             */
/*   Updated: 2025/04/04 06:42:03 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ft_list.h"
#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>
#include "ft_memory.h"
#include "env.h"

int     (*init_pipes(t_list *cmds))[2];
void	set_pipes(t_list *redirs, int cmd_index, int (*pipes)[2], int nb_cmds);
void	exec_cmds(t_list *cmds, t_list *envl);
void	free_tab(char **tab);
char	*find_cmd_path(char *cmd, char **envp);
void	close_pipes(int (*pipes)[2], int pipe_count);

#endif
