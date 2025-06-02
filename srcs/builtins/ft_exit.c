/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:20:44 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 17:55:55 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtins.h"

int	ft_exit(int argc, char **argv, t_msh *msh)
{
	if (argc > 2)
		return (EXIT_FAILURE);
	if (argc == 2)
		msh->exit_value = ft_atoi(argv[1]);
	msh->running = 0;
	return (EXIT_SUCCESS);
}
