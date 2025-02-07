/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/02/07 09:37:51 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_printf.h"
#include "parsing.h"
#include "minishell.h"

static void	print_token(void *content)
{
	char	*token;

	if (!content)
		return ;
	token = content;
	ft_printf("token: `%s`\n", token);
}

static void	print_redir(void *content)
{
	t_redir	*redir;

	if (!content)
		return ;
	redir = content;
	ft_printf("redir: %d\tfilename: %s\n", redir->type, redir->filename);
}

static void	print_cmd(void *content)
{
	t_cmd	*cmd;
	
	if (!content)
		return ;
	cmd = content;
	ft_printf("=== New command: ===\n");
	ft_lstiter(cmd->tokens, &print_token);
	ft_lstiter(cmd->redirs, &print_redir);
	ft_printf("====================\n\n");
}

int main(int argc, char const **argv, char const **envp)
{
	char	*rl;
	t_list	*cmds;

	(void)argc;
	(void)argv;
	(void)envp;
	// repl -> read eval print loop
	while (1)
	{
		rl = readline(PROMPT_STR);
		if (!rl)
			exit(EXIT_FAILURE);
		cmds = parsing(rl); // return a linked list of t_cmd
		ft_lstiter(cmds, &print_cmd);
		// execute
		free(rl);
	}
	return (EXIT_SUCCESS);
}
