/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:36:57 by marykman          #+#    #+#             */
/*   Updated: 2025/02/14 12:45:02 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "ft_list.h"

// Env variables are represented by a linked list containing strings
// formated like this: "[var_name]=[content]"

// Functions
/*
	env_get_content_by_name(const char *name)
	env_replace_by_name(const char *name)
	env_
*/

t_list	*env_get_var(t_list *envl, const char *name);
char	*env_get_var_content(t_list *envl, const char *name);
void	env_set_var(void);

// Utils
t_list	*strs_to_lst(char **strs);
char	**lst_to_strs(t_list *lst);

#endif
