/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:25:54 by marykman          #+#    #+#             */
/*   Updated: 2025/05/24 19:47:21 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "parsing.h"

typedef enum e_expander_error
{
	EXPANDER_SUCCESS,
	EXPANDER_QUOTING_ERROR
}	t_expander_error;

char	*expand(char *token, t_list *envl);
char	*ft_substr_expand(char *s, unsigned int start, size_t len,
	t_list *envl);

// Utils
void	add_to_strs(t_list **strs, char *str);

#endif
