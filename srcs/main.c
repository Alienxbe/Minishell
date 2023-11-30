/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:28:09 by marykman          #+#    #+#             */
/*   Updated: 2023/10/28 19:07:07 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "minishell.h"
#include <ft_stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_string.h"
#include <stdlib.h>

#include <stdbool.h>

static char	*get_prompt()
{
	return "msh@pwd~> ";
}

int	main(int argc, char **argv, char **envp)
{
	char	*buffer;

	(void)argc;
	(void)argv;
	(void)envp;

	// ft_printf("Argv:\n");
	// for (int i = 0; i < argc; i++)
	// 	ft_printf("[%02d]: `%s`\n", i, argv[i]);
	// ft_printf("\n\nEnvp:\n");
	// for (int i = 0; envp[i]; i++)
	// 	ft_printf("[%02d]: `%s`\n", i, envp[i]);

	while (1)
	{
		buffer = readline(get_prompt());
		if (ft_strncmp("exit", buffer, 5) == 0)
			break;
		/**
		 * todo: parse()
		 * todo: exec()
		 */
		add_history(buffer);
		free(buffer);
	}
	free(buffer);
	rl_clear_history();
	return (0);
}
