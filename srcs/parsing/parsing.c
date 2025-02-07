/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:58:22 by marykman          #+#    #+#             */
/*   Updated: 2025/02/07 09:41:39 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*parsing(const char *input)
{
	t_list	*cmds;
	t_list	*new;
	size_t	pos;

	cmds = NULL;
	pos = 0;
	while (input[pos])
	{
		skip_spaces(input, &pos);
		new = ft_lstnew(get_cmd(input, &pos));
		if (!new)
			return (NULL);	// EXIT
		ft_lstadd_back(&cmds, new);
		if (input[pos])
			pos++;
	}
	return (cmds);
}

