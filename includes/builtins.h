/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:36:33 by marykman          #+#    #+#             */
/*   Updated: 2025/04/26 07:14:01 by marykman         ###   ########.fr       */
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

typedef void	(*t_builtin)(char **, t_list *);

t_builtin	get_builtin_by_name(char *name);
void		ft_echo(char **argv, t_list *envl);
void		ft_pwd(char **argv, t_list *envl);
void		ft_cd(char **argv, t_list *envl);
void		ft_env(char **argv, t_list *envl);
void		ft_export(char **argv, t_list *envl);
void		ft_unset(char **argv, t_list *envl);
void		ft_exit(char **argv, t_list *envl);

#endif
