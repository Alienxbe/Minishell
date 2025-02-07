/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:39:43 by marykman          #+#    #+#             */
/*   Updated: 2025/02/07 09:40:20 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_ctype.h"

void	skip_spaces(const char *input, size_t *pos)
{
	while (ft_isspace(input[*pos]))
		(*pos)++;
}
