/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:39:43 by marykman          #+#    #+#             */
/*   Updated: 2025/05/24 21:27:13 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "ft_ctype.h"
#include "ft_list.h"

void	skip_spaces(const char *input, size_t *pos)
{
	while (ft_isspace(input[*pos]))
		(*pos)++;
}

t_bool	add_element(t_list **lst, void *element)
{
	t_list	*new;

	if (!element)
		return (false);
	new = ft_lstnew(element);
	if (!new)
	{
		free(element);
		return (false);
	}
	return (ft_lstadd_back(lst, new));
}
