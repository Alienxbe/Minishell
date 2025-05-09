/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 07:19:24 by marykman          #+#    #+#             */
/*   Updated: 2025/05/09 15:29:13 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "env.h"
#include "builtins.h"

static void	update_pwd(t_list **envl)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	env_del_var(envl, "PWD");
	env_add_var(envl, "PWD", getcwd(NULL, 0));
	free(pwd);
}

int	ft_cd(int argc, char **argv, t_list *envl)
{
	char	*path;

	if (argc > 2)
		return (builtin_print_error(TOO_MANY_ARGS, argv[0], NULL));
	path = argv[1];
	if (argc == 1)
		path = env_get_var_content(envl, "HOME");
	if (!path)
		return (builtin_print_error(MISSING_HOME, argv[0], NULL));
	if (chdir(path) < 0)
		return (builtin_print_error(NO_FILE, argv[0], path));
	update_pwd(&envl);
	return (EXIT_SUCCESS);
}
