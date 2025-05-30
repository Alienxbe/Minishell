/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:36:57 by marykman          #+#    #+#             */
/*   Updated: 2025/05/09 15:19:58 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "ft_list.h"

// Env variables are represented by a linked list containing strings
// formated like this: "[var_name]=[content]"

t_bool	env_del_var(t_list **envl, const char *name);
t_list	*env_add_var(t_list **envl, const char *name, char *content);
t_list	*env_cat_var(t_list **envl, const char *name, const char *str);

t_list	*env_get_var(t_list *envl, const char *name);
char	*env_get_var_content(t_list *envl, const char *name);

// Utils
t_list	*strs_to_lst(char **strs);
char	**lst_to_strs(t_list *lst);

#endif
