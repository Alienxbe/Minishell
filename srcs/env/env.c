/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:36:17 by marykman          #+#    #+#             */
/*   Updated: 2025/04/28 12:47:42 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_string.h"
#include "env.h"

/**
 * @brief Return the list pointer to the environnement variable in envl.
 * Return NULL if not found
 * 
 * @param envl Environnement list
 * @param name Variable name
 * @return t_list* Corresponding envl element
 */
t_list	*env_get_var(t_list *envl, const char *name)
{
	char	*str;
	size_t	name_len;
	size_t	var_len;

	if (!envl || !name)
		return (NULL);
	name_len = ft_strlen(name);
	while (envl)
	{
		str = envl->content;
		var_len = ft_strchr(str, '=') - str;
		if (var_len == name_len && !ft_strncmp(str, name, var_len))
			return (envl);
		envl = envl->next;
	}
	return (NULL);
}

/**
 * @brief Safely return the string pointed by the environnement variable in envl.
 * Return NULL if not found
 * 
 * @param envl Environnement list
 * @param name Variable name
 * @return char* Corresponding static string -> Can't be manipulated outside the function
 */
char	*env_get_var_content(t_list *envl, const char *name)
{
	t_list	*var;

	if (!envl || !name)
		return (NULL);
	var = env_get_var(envl, name);
	if (!var)
		return (NULL);
	return (ft_strchr(var->content, '=') + 1);
}
