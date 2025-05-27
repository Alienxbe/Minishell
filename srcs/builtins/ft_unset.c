/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:22:58 by marykman          #+#    #+#             */
/*   Updated: 2025/05/11 16:59:27 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"
#include "builtins.h"

int	ft_unset(int argc, char **argv, t_list **envl)
{
	int	i;

	i = 0;
	while (++i < argc)
		env_del_var(envl, argv[i]);
	return (EXIT_SUCCESS);
}
