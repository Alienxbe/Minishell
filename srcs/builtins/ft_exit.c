/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:20:44 by marykman          #+#    #+#             */
/*   Updated: 2025/05/11 16:58:44 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtins.h"

int	ft_exit(int argc, char **argv, t_list **envl)
{
	(void)argc;
	(void)argv;
	(void)envl;
	return (EXIT_SUCCESS);
}
