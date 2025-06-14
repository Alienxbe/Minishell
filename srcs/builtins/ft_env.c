/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:20:14 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 22:48:58 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_printf.h"
#include "env.h"
#include "builtins.h"

static void	print_env_var(void *content)
{
	ft_printf("%s\n", (char *)content);
}

int	ft_env(int argc, char **argv, t_msh *msh)
{
	char	*content;

	(void)argc;
	(void)argv;
	if (argc == 1)
		ft_lstiter(msh->envl, &print_env_var);
	else if (argc == 2)
	{
		content = env_get_var_content(msh->envl, argv[1]);
		if (content)
			ft_printf("%s\n", content);
		else
			return (builtin_print_error(MISSING_VAR, "env", argv[1]));
	}
	return (EXIT_SUCCESS);
}
