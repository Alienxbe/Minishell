/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:12:47 by marykman          #+#    #+#             */
/*   Updated: 2025/01/24 02:50:20 by marykman         ###   ########.fr       */
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
		ft_printf("new command prompted : `%s`\n", rl);
		if (rl)
			free(rl);
	}
	return (0);
}
