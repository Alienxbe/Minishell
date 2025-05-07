/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/05/07 19:07:14 by vpramann         ###   ########.fr       */
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

int	main(int argc, char const **argv, char **envp)
{
	char		*rl;
	t_cmd_table	cmd_table;
	t_list		*envl;
	// char	*prompt;

	(void)argc;
	(void)argv;
	(void)envp;
	envl = strs_to_lst(envp);
	// printf("%s\n", env_get_var_content(envl, "PWD"));
	// repl -> read eval print loop
	while (1)
	{
		start_signals();
		// prompt = ft_strjoinx(3, FT_GREEN"Minishesh "FT_RESETCOL, env_get_var_content(envl, "PWD"), " $ ");
		rl = readline(PROMPT_STR);
		// free(prompt);
		if (!rl)
			exit(EXIT_FAILURE);
		cmd_table.cmds = parsing(rl); // return a linked list of t_cmd
		cmd_table.cmd_count = ft_lstsize(cmd_table.cmds);
		free(rl);
		exec_cmds(&cmd_table, envl);
	}
	return (EXIT_SUCCESS);
}
