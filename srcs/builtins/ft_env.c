/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:20:14 by marykman          #+#    #+#             */
/*   Updated: 2025/05/03 19:23:11 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_printf.h"
#include "env.h"
#include "builtins.h"

static void	print_env_var(void *content)
{
	ft_printf("%s\n", (char *)content);
}

void	ft_env(int argc, char **argv, t_list *envl)
{
	char	*content;

	(void)argc;
	(void)argv;
	if (argc == 1)
		ft_lstiter(envl, &print_env_var);
	else if (argc == 2)
	{
		content = env_get_var_content(envl, argv[1]);
		if (content)
			ft_printf("%s\n", content);
	}
}
