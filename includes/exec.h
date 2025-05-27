/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:34:21 by marykman          #+#    #+#             */
/*   Updated: 2025/05/27 19:28:39 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ft_list.h"
# include "minishell.h"
# include "parsing.h"
# include <stdlib.h>
# include <unistd.h>
# include "ft_memory.h"
# include "env.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "builtins.h"
# include "ft_printf.h"
# include "expander.h"

extern int	g_last_ret;
void	set_pipes_redirs(t_list *redirs, int cmd_index,
			int (*pipes)[2], int nb_cmds);
void	exec_cmds(t_cmd_table *cmd_table, t_list **envl);
void	free_tab(char **tab);
char	*find_cmd_path(char *cmd, char **envp);
void	close_pipes(int (*pipes)[2], int pipe_count);
void	child_process(char **to_ex, t_list **envl,
			int (*pipes)[2], int nb_cmds);
void	parent_process(t_list **pids);
void	close_files(t_list *redirs);
int		has_absolute_path(char *cmd);
int		has_relative_path(char *cmd);
int		is_redir(t_list *redirs, t_redir_type type);
void	start_signals(void);
void	start_signals_exec(void);
void	free_pids(t_list **pids);
int		get_string_tab_len(char **tab);
void	exit_child_process(char **to_ex, char **envc);

#endif
