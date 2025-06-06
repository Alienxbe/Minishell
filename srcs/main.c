/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/06/06 14:31:50 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_string.h"
#include "env.h"
#include "parsing.h"
#include "expander.h"
#include "exec.h"
#include "minishell.h"

static void	incr_shlvl(t_list **envl)
{
	int		shlvl;
	char	*shlvl_str;

	shlvl = ft_atoi(env_get_var_content(*envl, "SHLVL"));
	shlvl_str = ft_itoa(shlvl + 1);
	if (!shlvl_str)
		return ;
	env_del_var(envl, "SHLVL");
	env_add_var(envl, "SHLVL", shlvl_str);
	free(shlvl_str);
}

static t_msh	init_msh(char **envp)
{
	t_msh	msh;

	msh = (t_msh){0};
	msh.envl = strs_to_lst(envp);
	if (!msh.envl)
		return (msh);
	msh.exit_value = EXIT_SUCCESS;
	msh.running = true;
	incr_shlvl(&msh.envl);
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
			exit(EXIT_SUCCESS);
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
