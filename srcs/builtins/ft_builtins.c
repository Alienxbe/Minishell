/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:38:25 by marykman          #+#    #+#             */
/*   Updated: 2025/04/25 15:39:39 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "builtins.h"

int builtins_index(char *name)
{
	char		**names;
	t_buildins	*functions;
	size_t		name_len;
	size_t		i;

	names = (char **){"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	functions = (t_buildins *){&ft_cd, &ft_echo, &ft_env, &ft_exit, &ft_export, &ft_pwd, &ft_pwd, &ft_unset};
	name_len = ft_strlen(name);
	i = -1;
	while (name[++i])
		if (ft_strlen())
}