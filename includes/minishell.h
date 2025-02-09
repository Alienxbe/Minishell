/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:36:42 by marykman          #+#    #+#             */
/*   Updated: 2025/02/09 19:12:42 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_list.h"
# include "ft_string.h"
# include <unistd.h>
# include <fcntl.h>
# include "parsing.h"
# include <stdlib.h>


# define PROMPT_STR	"\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"

const char	*get_paths(char **envp);
char	*find_cmd_path(char *cmd, char **envp);
char	*find_path(char **paths, char **cmds, int i);
char    **find_cmds(t_list *cmds);
void    exec_cmd(t_list *cmds, char **envp);

#endif
