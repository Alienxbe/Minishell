/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:34:21 by marykman          #+#    #+#             */
/*   Updated: 2025/06/06 22:30:34 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ft_list.h"
# include "minishell.h"
# include "parsing.h"

void	exec_cmds(t_msh *msh);
void	set_pipes_redirs(t_cmd *cmd, t_cmd_table *cmd_table);
int		open_infile(t_redir *redir, int *fd_io);
void	open_heredoc(t_redir *redir, int *fd_io);
int		open_outfile(t_redir *redir, int *fd_io);
void	free_tab(char **tab);
char	*find_cmd_path(char *cmd, char **envp);
void	close_pipes(int (*pipes)[2], int pipe_count);
void	child_process(char **to_ex, t_cmd_table *cmd_table, t_list **envl);
void	parent_process(t_list *cmds);
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
