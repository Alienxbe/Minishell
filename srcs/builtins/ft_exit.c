/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:20:44 by marykman          #+#    #+#             */
/*   Updated: 2025/06/08 19:23:27 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_math.h"
#include "ft_string.h"
#include "builtins.h"

int	ft_exit(int argc, char **argv, t_msh *msh)
{
	char	*endptr;

	if (argc > 2)
	{
		builtin_print_error(TOO_MANY_ARGS, argv[0], NULL);
		return (EXIT_FAILURE);
	}
	if (argc == 2)
	{
		msh->exit_value = (unsigned char)ft_strtol(argv[1], &endptr,
				BASE_DECI);
		if (*endptr != '\0')
		{
			builtin_print_error(NON_NUM_ARG, argv[0], argv[1]);
			msh->exit_value = 2;
		}
	}
	msh->running = 0;
	return (EXIT_SUCCESS);
}
