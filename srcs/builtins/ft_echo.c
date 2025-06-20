/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:46:28 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 19:07:50 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "ft_string.h"
#include "ft_printf.h"
#include "builtins.h"

t_bool	isoption(const char *str, const char option_name)
{
	size_t	i;

	if (!str)
		return (false);
	if (!ft_strstartwith(str, "-"))
		return (false);
	i = 0;
	while (str[++i])
		if (str[i] != option_name)
			return (false);
	return (true);
}

int	ft_echo(int argc, char **argv, t_msh *msh)
{
	size_t	i;
	t_bool	has_option;

	(void)argc;
	(void)msh;
	has_option = isoption(argv[1], 'n');
	i = 1;
	while (argv[i] && isoption(argv[i], 'n'))
		i++;
	while (argv[i])
	{
		ft_printf("%s", argv[i++]);
		if (argv[i])
			ft_printf(" ");
	}
	if (!has_option)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
