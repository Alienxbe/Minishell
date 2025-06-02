/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:36:42 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 18:21:31 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_list.h"
# include "ft_bool.h"

# define PROMPT_STR	"\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"

typedef struct s_cmd_table
{
	t_list	*cmds;
	size_t	cmd_count;
	int		(*pipes)[2];
	t_list	*pids;
	int		exit_value;
}	t_cmd_table;

typedef struct s_msh
{
	t_cmd_table	cmd_table;
	t_list		*envl;
	t_bool		running;
	int			previous_exit_value;
	int			exit_value;
}	t_msh;

#endif
