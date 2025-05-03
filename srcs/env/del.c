/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:00:34 by marykman          #+#    #+#             */
/*   Updated: 2025/05/03 19:20:51 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "env.h"

t_bool	env_del_var(t_list **envl, const char *name)
{
	t_list	*var;
	
	var = env_get_var(*envl, name);
	if (!var)
		return (false);
	ft_lstdelone(ft_lstremove(envl, var), &free);
	return (true);
}