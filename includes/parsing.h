/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:20:15 by marykman          #+#    #+#             */
/*   Updated: 2025/06/06 22:03:01 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stddef.h>
# include "ft_list.h"
# include "minishell.h"

# define TOKEN_DELIMITER	"<>|"
# define QUOTE_TYPES		"\'\""

typedef enum e_redir_type
{
	REDIR_STDIN,
	REDIR_STDOUT,
	REDIR_HEREDOC,
	REDIR_STDOUT_APPEND
}	t_redir_type;

/*
** Simple basic command
** Ex: ls -la > outfile
** 	tokens: "ls" "-la"
** 	redirection: output->"outfile"
*/
typedef struct s_redir
{
	char			*filename;
	t_redir_type	type;
	t_list			*heredoc;
}	t_redir;

typedef struct s_cmd
{
	t_list	*tokens; // ->content = char *
	t_list	*redirs; // ->content = t_redir *
	size_t	index;
	int		exit_status;
	int		pid;
}	t_cmd;

// Parsing
t_list	*parsing(const char *input, t_msh *msh);
t_cmd	*get_cmd(const char *input, size_t *pos, size_t index, t_msh *msh);
char	*get_token(const char *input, size_t *pos, t_msh *msh);
t_redir	*get_redir(const char *input, size_t *pos, t_msh *msh);

void	free_cmd(void *cmd);
void	free_redir(void *redir);

// Utils
void	skip_spaces(const char *input, size_t *pos);
t_bool	add_element(t_list **lst, void *element);

#endif
