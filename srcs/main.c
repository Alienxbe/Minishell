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

int	main(int argc, char **argv, char **envp)
{
	ft_printf("Argv:\n");
	for (int i = 0; i < argc; i++)
		ft_printf("[%02d]: `%s`\n", i, argv[i]);
	ft_printf("\n\nEnvp:\n");
	for (int i = 0; envp[i]; i++)
		ft_printf("[%02d]: `%s`\n", i, envp[i]);
	return (0);
}
