/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:25:54 by marykman          #+#    #+#             */
/*   Updated: 2025/05/24 10:06:08 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "parsing.h"

char	*expand(char *token, t_list *envl);
char	*ft_substr_expand(char *s, unsigned int start, size_t len,
	t_list *envl);

// Utils
void	add_to_strs(t_list **strs, char *str);

#endif
