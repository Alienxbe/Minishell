/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:33:58 by marykman          #+#    #+#             */
/*   Updated: 2025/05/24 21:27:00 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"
#include "parsing.h"

void	free_redir(void *redir)
{
	if (!redir)
		return ;
	free(((t_redir *)redir)->filename);
	free(redir);
}

t_redir	*get_redir(const char *input, size_t *pos, t_list *envl)
{
	t_redir		*redir;
	int			len;

	redir = ft_calloc(1, sizeof(*redir));
	if (!redir)
		return (NULL);	// EXIT
	len = 1 + (input[*pos + 1] == '<' || input[*pos + 1] == '>');
	redir->type = (input[*pos] == '>') + ((len - 1) << 1);
	(*pos) += len;
	skip_spaces(input, pos);
	redir->filename = get_token(input, pos, envl);
	return (redir);
}
