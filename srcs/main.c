/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/02/05 16:00:36 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_printf.h"
#include "minishell.h"
	
int main(int argc, char const **argv, char const **envp)
{
	char	*rl;

	(void)argc;
	(void)argv;
	(void)envp;
	// repl -> read eval print loop
	while (1)
	{
		rl = readline(PROMPT_STR);
		if (!rl)
			exit(EXIT_FAILURE);
		parsing(rl); // return a linked list of t_cmd
		// execute
		free(rl);
	}
	return (EXIT_SUCCESS);
}
