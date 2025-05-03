/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:39:58 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/03 12:49:28 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "exec.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*find_path(char **paths, char *cmd)
{
	char	*path;
	char	*cmdpath;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmdpath = ft_strjoin(path, cmd);
		if (access(cmdpath, F_OK | X_OK) == 0)
			return (free(path), cmdpath);
		i++;
	}
	if (!paths[i])
	{
		cmdpath = ft_strdup(cmd);
		if (!cmdpath)
		{
			free(path);
			exit (1);
		}
	}
	return (cmdpath);
}

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmdpath;

	paths = get_env_paths(envp);
	if (!paths)
	{
		cmdpath = ft_strdup(cmd);
		if (!cmdpath)
			exit (1);
	}
	else
	{
		cmdpath = find_path(paths, cmd);
		free_tab(paths);
	}
	return (cmdpath);
}

int has_relative_path(char *cmd)
{
	int i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int has_absolute_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '/')
		return (1);
	return (0);
}
