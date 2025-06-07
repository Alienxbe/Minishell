/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:36:33 by marykman          #+#    #+#             */
/*   Updated: 2025/06/07 16:34:38 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ft_list.h"
# include "ft_string.h"
# include "minishell.h"

/*
** Builtins prototype will always be similar
**
** @param argv is the same format as argv in the main
**
** @param envl is the same format as envp in the main except it's made of
** linked list
** for easier manipulation
*/

# define ERROR_MSG_TOO_MANY_ARGS	"too many arguments"
# define ERROR_MSG_NO_FILE			"No such file or directory"
# define ERROR_MSG_MISSING_HOME		"HOME not set"
# define ERROR_MSG_MISSING_VAR		"Variable not set"
# define ERROR_MSG_NON_NUM_ARG		"numeric argument required"

typedef int	(*t_builtin)(int, char **, t_msh *);

typedef enum e_builtin_error
{
	TOO_MANY_ARGS,
	NO_FILE,
	MISSING_HOME,
	MISSING_VAR,
	NON_NUM_ARG,
	BUILTIN_ERROR_LEN
}	t_builtin_error;

t_builtin	get_builtin_by_name(char *name);
int			ft_echo(int argc, char **argv, t_msh *msh);
int			ft_pwd(int argc, char **argv, t_msh *msh);
int			ft_cd(int argc, char **argv, t_msh *msh);
int			ft_env(int argc, char **argv, t_msh *msh);
int			ft_export(int argc, char **argv, t_msh *msh);
int			ft_unset(int argc, char **argv, t_msh *msh);
int			ft_exit(int argc, char **argv, t_msh *msh);

int			builtin_print_error(t_builtin_error error, const char *cmd_name,
				const char *filename);

#endif
