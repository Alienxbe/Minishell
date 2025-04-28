/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:19:24 by marykman          #+#    #+#             */
/*   Updated: 2025/04/28 13:13:10 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "env.h"
#include "builtins.h"

void	ft_cd(int argc, char **argv, t_list *envl)
{
	char	*home_path;

	(void)argc;
	(void)argv;
	(void)envl;
	if (argc == 1)
	{
		home_path = env_get_var_content(envl, "HOME");
		if (home_path)
			chdir(home_path);
		else
			ft_printf("minishell: cd : HOME not set\n");
	}
	if (argc == 2)
		chdir(argv[1]);
}
