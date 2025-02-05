/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/01/31 13:21:35 by marykman         ###   ########.fr       */
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
	while (1)
	{
		rl = readline(PROMPT_STR);
		if (!rl)
			exit(EXIT_FAILURE);
		parsing(rl);
		free(rl);
	}
	return (EXIT_SUCCESS);
}
