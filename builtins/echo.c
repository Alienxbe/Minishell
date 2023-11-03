/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:21:57 by xadabunu          #+#    #+#             */
/*   Updated: 2023/11/03 13:19:22 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

static int	is_flag(const char *word)
{
	int	i;

	i = 1;
	if (ft_strncmp("-n", word, 2) == 0)
	{
		i = 2;
		while (word[i])
		{
			if (word[i] != 'n')
				return (0);
			++i;
		}
		return (1);
	}
	return (0);
}

static bool	check_flag(const char **cmd, int *pos)
{
	int		i;
	bool	has_flag;

	i = 0;
	has_flag = false;
	while (cmd[i])
	{
		if (is_flag(cmd[i]))
		{
			(*pos)++;
			has_flag = true;
		}
		else
			break ;
		++i;
	}
	return (has_flag);
}

static int	write_error(void)
{
	write(STDOUT_FILENO, "write: no space to write\n", 25);
	return (1);
}

int	ft_echo(const char **cmd)
{
	bool	has_flag;
	int		pos;
	int		ret;

	pos = 1;
	ret = 0;
	has_flag = check_flag(cmd, &pos);
	while (cmd[pos])
	{
		ret = write(STDOUT_FILENO, cmd[pos], ft_strlen(cmd[pos]));
		if (ret == -1)
			return (write_error());
		++pos;
	}
	if (!has_flag)
		ret = write(STDOUT_FILENO, "\n", 1);
	if (ret == -1)
		return (write_error());
	return (0);
}
