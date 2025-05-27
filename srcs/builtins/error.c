/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:19:48 by marykman          #+#    #+#             */
/*   Updated: 2025/05/10 01:39:29 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "builtins.h"

int	builtin_print_error(t_builtin_error error, const char *cmd_name,
	const char *filename)
{
	char	**error_msg;

	error_msg = (char *[]){
		ERROR_MSG_TOO_MANY_ARGS,
		ERROR_MSG_NO_FILE,
		ERROR_MSG_MISSING_HOME,
		ERROR_MSG_MISSING_VAR};
	if (error >= BUILTIN_ERROR_LEN)
		return (EXIT_FAILURE);
	ft_fprintf(STDERR_FILENO, "Minishell: %s: ", cmd_name);
	if (filename)
		ft_fprintf(STDERR_FILENO, "%s: ", filename);
	ft_fprintf(STDERR_FILENO, "%s\n", error_msg[error]);
	return (EXIT_FAILURE);
}
