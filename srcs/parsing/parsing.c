/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:58:22 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 18:15:09 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*parsing(const char *input, t_msh *msh)
{
	t_list	*cmds;
	size_t	pos;
	size_t	index;

	cmds = NULL;
	pos = 0;
	index = 0;
	while (input[pos])
	{
		skip_spaces(input, &pos);
		if (!add_element(&cmds, get_cmd(input, &pos, index++, msh)))
		{
			ft_lstclear(&cmds, free_cmd);
			return (NULL);
		}
		if (input[pos])
			pos++;
	}
	return (cmds);
}

