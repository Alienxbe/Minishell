/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/03/07 00:17:52 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_colors.h"
#include "ft_printf.h"
#include "env.h"
#include "parsing.h"
#include "exec.h"
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

int main(int argc, char const **argv, char **envp)
{
	char		*rl;
	t_cmd_table	cmd_table;
	t_list		*envl;
	int i = 0;
	// char	*prompt;

	(void)argc;
	(void)argv;
	(void)envp;
	envl = strs_to_lst(envp);
	// printf("%s\n", env_get_var_content(envl, "PWD"));
	// repl -> read eval print loop
	while (i == 0)
	{
		// prompt = ft_strjoinx(3, FT_GREEN"Minishesh "FT_RESETCOL, env_get_var_content(envl, "PWD"), " $ ");
		rl = readline(PROMPT_STR);
		// fr ee(prompt);
		if (!rl)
			exit(EXIT_FAILURE);
		cmd_table.cmds = parsing(rl); // return a linked list of t_cmd
		cmd_table.cmd_count = ft_lstsize(cmd_table.cmds);
		free(rl);
		exec_cmds(cmds, envl);
	}
	return (EXIT_SUCCESS);
}
