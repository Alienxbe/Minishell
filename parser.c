#include <stddef.h>
#include "ft_ctype.h"

typedef enum e_token_type
{
	REDIRECTION_TOKEN, //-> node has file to redir to
	HEREDOC_TOKEN, //-> node has file with input
	PIPE_TOKEN, //-> node has left and right to exec
	BUILTIN_TOKEN, //-> builtins cmds to exec in current shell
	//? $_TOKEN pour les variables à interpréter
	COMMAND_TOKEN, //-> extra cmds to exec in subshell
	BTW_QUOTE_TOKEN, //-> '"$USER"' -> "$USER"
	BTW_DBL_QUOTE_TOKEN //-> "'$USER'" -> 'bunu'
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	void			*value;
}	t_token;

t_token	*scan_token(const char *str)
{
	size_t	i;

	while (str[i] && ft_isspace(str[i]))
		++i;
	
	/*
	?	while str[i] coorespond au bon char ?
	*  -> if starts w/ char	-> token ends when space, |, ', ", redir met
	*  -> if starts w/ \d	-> token ends when any non \d met (float ?)
	*  -> if starts w/ </>	-> can only be >, >>, <, <<
	*  		&& next token has to be file path/name or heredoc
	*  -> if starts w/ ', "	-> until corresponding quote is met (parse inside ?)
	*/
}

char	*str_to_tree(const char *str)
{
	unsigned int	i;
	char	*token;

	i = 0;
	while (str[i])
	{
		token = scan_token(str);
		/*
		todo: depending on the token retrieved
		todo: 	-> a certain kind of node is added
		todo:		to the tree that will be returned
		*/ 
		++i;
	}
}
