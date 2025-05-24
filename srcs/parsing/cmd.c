/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:19:59 by marykman          #+#    #+#             */
/*   Updated: 2025/05/16 01:20:09 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_list.h"
#include "parsing.h"

t_cmd	*get_cmd(const char *input, size_t *pos, t_list *envl)
{
	t_cmd	*cmd;
	t_list	*new;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	while (input[*pos] && input[*pos] != '|')
	{
		if (input[*pos] == '<' || input[*pos] == '>')
		{
			new = ft_lstnew(get_redir(input, pos, envl));
			if (!new)
				return (NULL);	// EXIT
			ft_lstadd_back(&cmd->redirs, new);
		}
		else
		{
			new = ft_lstnew(get_token(input, pos, envl));
			if (!new)
				return (NULL);	// EXIT
			ft_lstadd_back(&cmd->tokens, new);
		}
		skip_spaces(input, pos);
	}
	return (cmd);
}
