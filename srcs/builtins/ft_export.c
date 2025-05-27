/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:21:32 by marykman          #+#    #+#             */
/*   Updated: 2025/05/11 16:59:01 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_string.h"
#include "ft_bool.h"
#include "env.h"
#include "builtins.h"

#include "ft_printf.h"

static t_bool	is_valid_varname(const char *name, const char *end)
{
	size_t	i;

	if (!name)
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 0;
	while (name[++i] && name + i != end)
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
	return (true);
}

static char	*get_end_of_var_name(const char *str)
{
	char	*end_of_var_name;

	end_of_var_name = ft_strchr(str, '=');
	if (!end_of_var_name || end_of_var_name == str)
		return (NULL);
	if (*(end_of_var_name - 1) == '+')
		end_of_var_name--;
	return (end_of_var_name);
}

static void	export_var(t_list **envl, char *str)
{
	char	*end_of_var_name;
	char	*name;

	end_of_var_name = get_end_of_var_name(str);
	if (!end_of_var_name || !is_valid_varname(str, end_of_var_name))
	{
		builtin_print_error(MISSING_VAR, "export", str);
		return ;
	}
	name = ft_substr(str, 0, end_of_var_name - str);
	if (!name)
		return ;
	if (*end_of_var_name == '+')
		env_cat_var(envl, name, end_of_var_name + 2);
	else
	{
		env_del_var(envl, name);
		env_add_var(envl, name, end_of_var_name + 1);
	}
	free(name);
}

int	ft_export(int argc, char **argv, t_list **envl)
{
	int	i;

	i = 0;
	while (++i < argc)
		export_var(envl, argv[i]);
	return (EXIT_SUCCESS);
}
