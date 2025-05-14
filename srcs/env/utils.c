/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:59:32 by marykman          #+#    #+#             */
/*   Updated: 2025/05/14 15:30:46 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memory.h"
#include "ft_string.h"
#include "env.h"

static void	free_strs(char **strs)
{
	size_t	i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

t_list	*strs_to_lst(char **strs)
{
	t_list	*alst;
	t_list	*lst;
	char	*content;

	alst = NULL;
	if (!strs)
		return (NULL);
	while (*strs)
	{
		content = ft_strdup(*strs);
		if (!content)
			break ;
		lst = ft_lstnew(content);
		if (!lst)
		{
			free(content);
			break ;
		}
		ft_lstadd_back(&alst, lst);
		strs++;
	}
	if (*strs)
		ft_lstclear(&alst, &free);
	return (alst);
}

char	**lst_to_strs(t_list *lst)
{
	char	**strs;
	size_t	i;

	if (!lst)
		return (NULL);
	strs = ft_calloc(ft_lstsize(lst) + 1, sizeof(*strs));
	if (!strs)
		return (NULL);
	i = -1;
	while (lst)
	{
		strs[++i] = ft_strdup(lst->content);
		if (!strs[i])
			break ;
		lst = lst->next;
	}
	if (lst)
	{
		free_strs(strs);
		return (NULL);
	}
	return (strs);
}
