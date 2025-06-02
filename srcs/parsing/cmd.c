/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:19:59 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 18:33:06 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"
#include "ft_list.h"
#include "parsing.h"

#include "ft_printf.h"

void	free_cmd(void *cmd)
{
	if (!cmd)
		return ;
	ft_lstclear(&((t_cmd *)cmd)->tokens, free);
	ft_lstclear(&((t_cmd *)cmd)->redirs, free_redir);
	free(cmd);
}

t_cmd	*get_cmd(const char *input, size_t *pos, size_t index, t_msh *msh)
{
	t_cmd	*cmd;
	t_bool	ret;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	while (input[*pos] && input[*pos] != '|')
	{
		if (input[*pos] == '<' || input[*pos] == '>')
			ret = add_element(&cmd->redirs, get_redir(input, pos, msh));
		else
			ret = add_element(&cmd->tokens, get_token(input, pos, msh));
		if (!ret)
		{
			free_cmd(cmd);
			return (NULL);
		}
		skip_spaces(input, pos);
	}
	cmd->index = index;
	return (cmd);
}
