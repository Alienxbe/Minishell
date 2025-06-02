/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:24:04 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 18:12:20 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "ft_list.h"
#include "env.h"
#include "parsing.h"
#include "expander.h"

#include "ft_printf.h"

static void	expand_to_strs(char *token, t_list **strs, t_msh *msh)
{
	char	*next_quote;
	size_t	i;

	i = 0;
	while (token[i])
	{
		if (ft_strchr(QUOTE_TYPES, token[i]))
		{
			add_to_strs(strs, ft_substr(token, 0, i));
			token += i + 1;
			i = 0;
			next_quote = ft_strchr(token, token[i - 1]);
			if (token[i - 1] == '\'')
				add_to_strs(strs, ft_substr(token, 0, next_quote - token));
			else if (token[i - 1] == '\"')
				add_to_strs(strs, ft_substr_expand(token, 0,
						next_quote - token, msh));
			token = next_quote + 1;
		}
		else
			i++;
	}
	add_to_strs(strs, ft_substr_expand(token, 0, i, msh));
}

char	*expand(char *token, t_msh *msh)
{
	char	*str;
	t_list	*strs;

	strs = NULL;
	expand_to_strs(token, &strs, msh);
	str = ft_lststrjoin(strs, "");
	ft_lstclear(&strs, free);
	free(token);
	return (str);
}
