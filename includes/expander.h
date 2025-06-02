/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:25:54 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 18:11:13 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "parsing.h"
#include "minishell.h"

typedef enum e_expander_error
{
	EXPANDER_SUCCESS,
	EXPANDER_QUOTING_ERROR
}	t_expander_error;

char	*expand(char *token, t_msh *msh);
char	*ft_substr_expand(char *s, unsigned int start, size_t len, t_msh *msh);

// Utils
void	add_to_strs(t_list **strs, char *str);

#endif
