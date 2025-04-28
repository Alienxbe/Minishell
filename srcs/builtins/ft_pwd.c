/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:22:12 by marykman          #+#    #+#             */
/*   Updated: 2025/04/28 13:08:43 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "builtins.h"

void	ft_pwd(int argc, char **argv, t_list *envl)
{
	char	*pwd;

	(void)argc;
	(void)argv;
	(void)envl;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	ft_printf("%s\n", pwd);
	free(pwd);
}
