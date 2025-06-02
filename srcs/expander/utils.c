/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:26:50 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 18:10:18 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "env.h"
#include "exec.h"
#include "expander.h"

#include "ft_printf.h"

void	add_to_strs(t_list **strs, char *str)
{
	t_list	*new;

	if (!str)
		return ;
	if (!*str)
	{
		free(str);
		return ;
	}
	new = ft_lstnew(str);
	if (!new)
		free(str);
	ft_lstadd_back(strs, new);
}

static int	get_var_len(const char *str)
{
	int	len;

	if (str[0] == '?')
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	len = 1;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

static char	*get_var(const char *s, size_t var_pos, t_msh *msh)
{
	char	*varname;
	char	*content;

	varname = ft_substr(s, var_pos, get_var_len(s + var_pos));
	if (*varname == '?')
		content = ft_itoa(msh->previous_exit_value);
	else
		content = env_get_var_content(msh->envl, varname);
	free(varname);
	if (!content)
		content = "";
	return (content);
}

static void	s_to_strs(const char *s, size_t len, t_list **strs, t_msh *msh)
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
			add_to_strs(strs, ft_strdup(get_var(s, var_pos, msh)));
			i += get_var_len(s + var_pos) + 1;
			var_pos = i;
		}
		i++;
	}
	add_to_strs(strs, ft_substr(s, var_pos, len - var_pos));
}

char	*ft_substr_expand(char *s, unsigned int start, size_t len, t_msh *msh)
{
	char	*str;
	t_list	*strs;

	if (!s || !s[start])
		return (NULL);
	strs = NULL;
	s_to_strs(s + start, len, &strs, msh);
	if (!strs)
		return (ft_strdup(""));
	str = ft_lststrjoin(strs, "");
	ft_lstclear(&strs, free);
	return (str);
}
