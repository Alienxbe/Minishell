/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:38:56 by marykman          #+#    #+#             */
/*   Updated: 2025/05/24 10:05:59 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	add_to_strs(t_list **strs, char *str)
{
	t_list	*new;

	if (!str)
		return ;
	if (!*str)
	{
		free(str);
		return ;
	}
	new = ft_lstnew(str);
	if (!new)
		free(str);
	ft_lstadd_back(strs, new);
}