/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:39:58 by vpramann          #+#    #+#             */
/*   Updated: 2025/05/03 05:36:10 by victor           ###   ########.fr       */
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

/*const char	*get_paths(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}*/

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
			exit (1);
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

/*char	*find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*cmdpath;
	char	**cmds;

	i = -1;
	if (!cmd)
		return (NULL);
	cmds = ft_split(cmd, ' ');
	if (!cmds || !cmds[0])
		return (NULL);
	if (access(cmds[0], F_OK | X_OK) == 0)
		return (cmds[0]);
	if (!envp[0] || !get_paths(envp))
		return (NULL);
	paths = ft_split(get_paths(envp), ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		cmdpath = find_path(paths, cmds, i);
		if (cmdpath != NULL)
		{
			free_tab(paths);
			free_tab(cmds);
			return (cmdpath);
		}
		free (cmdpath);
	}
	free_tab(paths);
	free_tab(cmds);
	if (!cmdpath)
	{
		cmdpath = ft_strdup(cmds[0]);
		if (!cmdpath)
			return (NULL);
		return (cmdpath);
	}
	return (NULL);
}*/

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

char **find_cmds(t_list *cmds)
{
    char    **cmdss;
    int size;
    int i;
    t_cmd *cmd;
	t_list *tmp;

    i = 0;
    cmd = cmds->content; 
    size = ft_lstsize(cmd->tokens);
    cmdss = malloc(sizeof(char *) * (size + 1));
	if (!cmdss)
		return (NULL);
	tmp = cmd->tokens;
    while (tmp)
    {
        cmdss[i] = tmp->content;
        i++;
        tmp = tmp->next;
    }
	cmdss[i] = NULL;
    return (cmdss);
}
