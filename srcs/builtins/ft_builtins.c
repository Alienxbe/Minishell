/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:38:25 by marykman          #+#    #+#             */
/*   Updated: 2025/04/26 07:25:28 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "builtins.h"

t_builtin	get_builtin_by_name(char *name)
{
	char		**names;
	t_builtin	*functions;
	size_t		i;

	names = (char *[8]){"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	functions = (t_builtin [8]){&ft_cd, &ft_echo, &ft_env, &ft_exit, &ft_export, &ft_pwd, &ft_pwd, &ft_unset};
	i = -1;
	while (names[++i])
		if (!ft_strcmp(names[i], name))
			return (functions[i]);
	return (NULL);
}