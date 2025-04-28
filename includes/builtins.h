/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:36:33 by marykman          #+#    #+#             */
/*   Updated: 2025/04/28 13:04:37 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ft_list.h"

/*
** Builtins prototype will always be similar
** 
** @param argv is the same format as argv in the main
** 
** @param envl is the same format as envp in the main except it's made of linked list
** for easier manipulation
*/

typedef void	(*t_builtin)(int, char **, t_list *);

t_builtin	get_builtin_by_name(char *name);
void		ft_echo(int argc, char **argv, t_list *envl);
void		ft_pwd(int argc, char **argv, t_list *envl);
void		ft_cd(int argc, char **argv, t_list *envl);
void		ft_env(int argc, char **argv, t_list *envl);
void		ft_export(int argc, char **argv, t_list *envl);
void		ft_unset(int argc, char **argv, t_list *envl);
void		ft_exit(int argc, char **argv, t_list *envl);

#endif
