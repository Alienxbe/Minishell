/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:26:45 by marykman          #+#    #+#             */
/*   Updated: 2025/05/09 15:36:24 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "env.h"

t_list	*env_cat_var(t_list **envl, const char *name, const char *str)
{
	char	*new_str;

	if (!str || !name)
		return (false);
	new_str = env_get_var_content(*envl, name);
	if (new_str)
		new_str = ft_strjoin(new_str, str);
	else
		new_str = "";
	if (!new_str)
		return (false);
	env_del_var(envl, name);
	return (env_add_var(envl, name, new_str));
}
