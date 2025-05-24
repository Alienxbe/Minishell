/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:58:22 by marykman          #+#    #+#             */
/*   Updated: 2025/05/24 21:26:34 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*parsing(const char *input, t_list *envl)
{
	t_list	*cmds;
	size_t	pos;

	cmds = NULL;
	pos = 0;
	while (input[pos])
	{
		skip_spaces(input, &pos);
		if (!add_element(&cmds, get_cmd(input, &pos, envl)))
		{
			ft_lstclear(&cmds, free_cmd);
			return (NULL);
		}
		if (input[pos])
			pos++;
	}
	return (cmds);
}

