/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:47:57 by marykman          #+#    #+#             */
/*   Updated: 2025/05/10 00:56:00 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "env.h"

t_list	*env_add_var(t_list **envl, const char *name, char *content)
{
	char	*var;
	t_list	*lst;

	if (!content)
		content = "";
	var = ft_strjoinx(3, name, "=", content);
	if (!var)
		return (NULL);
	lst = ft_lstnew(var);
	if (!lst)
	{
		free(var);
		return (NULL);
	}
	ft_lstadd_back(envl, lst);
	return (lst);
}
