/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:20:15 by marykman          #+#    #+#             */
/*   Updated: 2025/02/07 17:58:14 by vpramann         ###   ########.fr       */
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
}	t_cmd;

typedef struct s_redir
{
	char			*filename;
	t_redir_type	type;
}	t_redir;

// Parsing
t_list	*parsing(const char *input);
t_cmd	*get_cmd(const char *input, size_t *pos);
char	*get_token(const char *input, size_t *pos);
t_redir	*get_redir(const char *input, size_t *pos);

// Utils
void	skip_spaces(const char *input, size_t *pos);

#endif
