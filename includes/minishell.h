/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:36:42 by marykman          #+#    #+#             */
/*   Updated: 2025/02/06 21:41:51 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_list.h"

# define PROMPT_STR	"\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"

typedef enum e_redir_type
{
	REDIR_STDIN,
	REDIR_STDOUT,
	REDIR_STDOUT_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

/*
** Simple basic command
** Ex: ls -la > outfile
** 	tokens: "ls" "-la"
** 	redirection: output->"outfile"
*/
typedef struct s_cmd
{
	t_list	*tokens;
	t_list	*redirs;
}	t_cmd;

typedef struct s_redir
{
	char			*filename;
	t_redir_type	type;
}	t_redir;

int	parsing(const char *input);

#endif
