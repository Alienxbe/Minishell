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
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h> //perror

static bool	is_a_number(const char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
		++i;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (str[i] > '9' && str[i] < '0')
			return (false);
		++i;
	}
	return (true);	
}

static uintmax_t	ft_strtoumax(const char *str)
{
	uintmax_t	res;
	size_t		i;

	res = 0;
	while (ft_isspace(str[i]))
		++i;
	while (str[i])
	{

	}
	return (res);
}

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
	//todo: clear everything before exit
	if (number_of_arguments == 0)
		exit(errno); //todo exit($?) how ?
	if (!is_a_number(args[1]))
	{
		perror(errno);
		exit(2);
	}
	exit((unsigned int)ft_atoi(args[0]) % 256); //?strtoumax ?
	return (0);
}
