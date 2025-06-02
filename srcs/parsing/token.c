/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:35:13 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 18:12:46 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_ctype.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "expander.h"
#include "parsing.h"

static int	is_token_delimiter(const char c)
{
	return (ft_isspace(c) || ft_strchr(TOKEN_DELIMITER, c));
}

static t_expander_error	skip_quotes(const char *input, size_t *len)
{
	char	*next;

	if (!ft_strchr(QUOTE_TYPES, input[*len]))
		return (EXPANDER_SUCCESS);
	next = ft_strchr(input + *len + 1, input[*len]);
	if (!next)
		return (EXPANDER_QUOTING_ERROR);
	(*len) = next - input;
	return (EXPANDER_SUCCESS);
}

char *get_token(const char *input, size_t *pos, t_msh *msh)
{
	char	*token;
	size_t	len;

	len = 0;
	while (input[*pos + len] && !is_token_delimiter(input[*pos + len]))
	{
		if (skip_quotes(input + *pos, &len) == EXPANDER_QUOTING_ERROR)
		{
			ft_fprintf(STDERR_FILENO, "Quoting error\n");
			return (NULL);
		}
		len++;
	}
	token = ft_substr(input, *pos, len);
	if (!token)
		return (NULL);	// EXIT
	*pos += len;
	token = expand(token, msh);
	return (token);
}
