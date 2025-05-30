/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:20:15 by marykman          #+#    #+#             */
/*   Updated: 2025/05/27 04:41:29 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include "ft_list.h"

# define TOKEN_DELIMITER	"<>|"
# define QUOTE_TYPES		"\'\""

typedef enum e_redir_type
{
	REDIR_STDIN,
	REDIR_STDOUT,
	REDIR_HEREDOC,
	REDIR_STDOUT_APPEND
}	t_redir_type;

typedef struct s_cmd_table
{
	t_list	*cmds;
	int		cmd_count;
	int		(*pipes)[2];
	t_list	*pids;
	int		last_ret;
}	t_cmd_table;

/*
** Simple basic command
** Ex: ls -la > outfile
** 	tokens: "ls" "-la"
** 	redirection: output->"outfile"
*/
typedef struct s_cmd
{
	t_list	*tokens; // ->content = char *
	t_list	*redirs; // ->content = t_redir *
	int    cmd_index;
}	t_cmd;

typedef struct s_redir
{
	char			*filename;
	t_redir_type	type;
	int				fd_io[2];
}	t_redir;

// Parsing
t_list	*parsing(const char *input, t_list *envl);
t_cmd	*get_cmd(const char *input, size_t *pos, t_list *envl);
char	*get_token(const char *input, size_t *pos, t_list *envl);
t_redir	*get_redir(const char *input, size_t *pos, t_list *envl);

void	free_cmd(void *cmd);
void	free_redir(void *redir);

// Utils
void	skip_spaces(const char *input, size_t *pos);
t_bool	add_element(t_list **lst, void *element);

#endif
