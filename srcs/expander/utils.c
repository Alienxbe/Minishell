/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:26:50 by marykman          #+#    #+#             */
/*   Updated: 2025/05/24 16:28:58 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "env.h"
#include "expander.h"

#include "ft_printf.h"

static int	get_var_len(const char *str)
{
	int	len;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	len = 1;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

static void	s_to_strs(const char *s, size_t len, t_list **strs, t_list *envl)
{
	size_t	i;
	size_t	var_pos;

	i = 0;
	var_pos = 0;
	while (i < len && s[i])
	{
		if (s[i] == '$')
		{
			add_to_strs(strs, ft_substr(s, var_pos, i - var_pos));
			var_pos = i + 1;
			// env var
			char *varname = ft_substr(s, var_pos, get_var_len(s + var_pos));
			char *content = env_get_var_content(envl, varname);
			// ft_printf("new var: `%s` -> `%s`\n", varname, content);
			free(varname);
			if (!content)
				content = "";
			add_to_strs(strs, ft_strdup(content));
			i += get_var_len(s + var_pos) + 1;
			var_pos = i;
		}
		i++;
	}
	add_to_strs(strs, ft_substr(s, var_pos, len - var_pos));
}

char	*ft_substr_expand(char *s, unsigned int start, size_t len,
	t_list *envl)
{
	char	*str;
	t_list	*strs;
	
	if (!s || !s[start])
		return (NULL);
	strs = NULL;
	s_to_strs(s + start, len, &strs, envl);
	if (!strs)
		return (ft_strdup(""));
	str = ft_lststrjoin(strs, "");
	ft_lstclear(&strs, free);
	return (str);
}