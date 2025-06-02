/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:22:12 by marykman          #+#    #+#             */
/*   Updated: 2025/06/02 17:56:41 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "builtins.h"

int	ft_pwd(int argc, char **argv, t_msh *msh)
{
	char	*pwd;

	(void)argc;
	(void)argv;
	(void)msh;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
