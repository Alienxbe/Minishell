/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 19:00:57 by marykman         ###   ########.fr       */
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
#include "expander.h"
#include "exec.h"
#include "minishell.h"

static t_msh	init_msh(char **envp)
{
	t_msh	msh;

	msh = (t_msh){0};
	msh.envl = strs_to_lst(envp);
	msh.exit_value = EXIT_SUCCESS;
	msh.running = true;
	return (msh);
}

static void	execute_cmd_table(t_msh *msh)
{
	msh->cmd_table.cmd_count = ft_lstsize(msh->cmd_table.cmds);
	exec_cmds(msh);
	msh->previous_exit_value = ((t_cmd *)(ft_lstlast(
					msh->cmd_table.cmds)->content))->exit_status;
	ft_lstclear(&msh->cmd_table.cmds, free_cmd);
}

int	main(int argc, char const **argv, char **envp)
{
	char	*rl;
	t_msh	msh;

	(void)argc;
	(void)argv;
	msh = init_msh(envp);
	while (msh.running)
	{
		start_signals();
		rl = readline(PROMPT_STR);
		if (!rl)
		{
			ft_lstclear(&msh.envl, free);
			exit(EXIT_FAILURE);
		}
		if (*rl)
			add_history(rl);
		msh.cmd_table = (t_cmd_table){0};
		msh.cmd_table.cmds = parsing(rl, &msh);
		if (msh.cmd_table.cmds)
			execute_cmd_table(&msh);
		free(rl);
	}
	ft_lstclear(&msh.envl, free);
	return (msh.exit_value);
}
