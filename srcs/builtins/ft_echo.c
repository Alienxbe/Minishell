/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:46:28 by marykman          #+#    #+#             */
/*   Updated: 2025/04/26 08:48:14 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"
#include "ft_printf.h"
#include "builtins.h"

t_bool	isoption(const char *str, const char option_name)
{
	size_t	i;

	if (!ft_strstartwith(str, "-"))
		return (false);
	i = 0;
	while (str[++i])
		if (str[i] != option_name)
			return (false);
	return (true);
}

void	ft_echo(char **argv, t_list *envl)
{
	size_t	i;
	t_bool	has_option;

	(void)envl;
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
}
