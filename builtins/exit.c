/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:29:34 by xadabunu          #+#    #+#             */
/*   Updated: 2023/11/03 14:09:18 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

static int	nb_args(char **args)
{
	if (!args || !args[0])
		return (0);
	if (args[1])
		return (2);
	return (1);
}

int	ft_exit(char **args)
{
	int	number_of_arguments;

	number_of_arguments = nb_args(args);
	if (number_of_arguments == 2)
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	exit((unsigned int)ft_atoi(args[0]) % 256);
	return (0);
}
