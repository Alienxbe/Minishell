/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:38:25 by marykman          #+#    #+#             */
/*   Updated: 2025/05/10 01:38:59 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "builtins.h"

t_builtin	get_builtin_by_name(char *name)
{
	char		**names;
	t_builtin	*functions;
	size_t		i;

	names = (char *[8]){"echo", "pwd", "cd", "env", "export", "unset", "exit",
		NULL};
	functions = (t_builtin [8]){&ft_echo, &ft_pwd, &ft_cd, &ft_env, &ft_export,
		&ft_unset, &ft_exit, NULL};
	i = -1;
	while (names[++i])
		if (!ft_strcmp(names[i], name))
			return (functions[i]);
	return (NULL);
}
