/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:35:13 by marykman          #+#    #+#             */
/*   Updated: 2025/02/07 09:59:19 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "parsing.h"

static int	is_token_delimiter(const char c)
{
	return (ft_isspace(c) || ft_strchr(TOKEN_DELIMITER, c));
}

static void	skip_quotes(const char *input, size_t *len)
{
	char	*next;

	if (!ft_strchr(QUOTE_TYPES, input[*len]))
		return ;
	next = ft_strchr(input + *len + 1, input[*len]);
	if (!next)
	{
		ft_printf("Quoting error\n");
		(*len)++;
		return ; // 	EXIT
	}
	(*len) += next - input;
}

char *get_token(const char *input, size_t *pos)
{
	char	*token;
	size_t	len;

	len = 0;
	while (input[*pos + len] && !is_token_delimiter(input[*pos + len]))
	{
		skip_quotes(input + *pos, &len);
		len++;
	}
	token = ft_substr(input, *pos, len);
	if (!token)
		return (NULL);	// EXIT
	*pos += len;
	return (token);
}
