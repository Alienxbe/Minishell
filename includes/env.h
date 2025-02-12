/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:36:57 by marykman          #+#    #+#             */
/*   Updated: 2025/02/12 17:13:14 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "ft_list.h"

// Env variables are represented by a linked list containing strings
// formated like this: "[var_name]=[content]"

// Functions
/*
	env_get_content_by_name(char *name)
	env_replace_by_name(char *name)
	env_
*/

// Utils
t_list	*strs_to_lst(char **strs);
char	**lst_to_strs(t_list *lst);
#endif
