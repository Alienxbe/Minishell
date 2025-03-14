/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:34:21 by marykman          #+#    #+#             */
/*   Updated: 2025/03/15 00:33:45 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "ft_list.h"

void        exec_cmds(t_list *cmds, t_list *envl);
static void exec_cmd(t_cmd *cmd,int cmd_index, t_list *envl);
static void exec(t_cmd *cmd, t_list *envl);
static void	set_pipes(t_list *redir, int cmd_index, int (*pipes)[2]);
static int	(*init_pipes(t_list *cmds))[2];
static char	*find_path(char **paths, char **cmds, int i);

#endif
