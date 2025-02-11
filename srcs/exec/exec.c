/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:39:58 by vpramann          #+#    #+#             */
/*   Updated: 2025/02/11 21:20:51 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

const char	*get_paths(char **envp)
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
}

char	*find_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*cmdpath;
	char	**cmds;

	i = -1;
	if (!cmd)
		return (NULL);
	cmds = ft_split(cmd, ' ');
	if (access(cmds[0], F_OK | X_OK) == 0)
		return (cmds[0]);
	if (!envp[0])
		return (NULL);
	paths = ft_split(get_paths(envp), ':');
	while (paths[++i])
	{
		cmdpath = find_path(paths, cmds, i);
		if (cmdpath != NULL)
			return (cmdpath);
		free (cmdpath);
	}
	return (NULL);
}

char	*find_path(char **paths, char **cmds, int i)
{
	char	*path;
	char	*cmdpath;

	path = ft_strjoin(paths[i], "/");
	cmdpath = ft_strjoin(path, cmds[0]);
	if (access(cmdpath, F_OK | X_OK) == 0)
		return (free(path), cmdpath);
	return (NULL);
}

char **find_cmds(t_list *cmds)
{
    char    **cmdss;
    int size;
    int i;
    t_cmd *cmd;

    i = 0;
    cmd = cmds->content; 
    size = ft_lstsize(cmd->tokens);
    cmdss = malloc(sizeof(char *) * size);
    while (cmd->tokens)
    {
        cmdss[i] = malloc (sizeof(char) * ft_strlen(cmd->tokens->content));
        cmdss[i] = cmd->tokens->content;
        i++;
        cmd->tokens = cmd->tokens->next;
    }
    return (cmdss);
}

void exec_cmd(t_list *cmds, char **envp)
{
    char	**cmdss;
	char	*path;

	if (!envp)
		return ;
	cmdss = find_cmds(cmds);
	path = find_cmd_path(cmdss[0], envp);
	if (execve(path, cmdss, envp) == -1)
	{
		/*free(path);
		free_tab(cmdss);*/
		return ;
	}
}

void exec_cmds(t_list *cmds, char ** envp)
{
	t_cmd *cmd;
	int pipe_fds[2];
	t_redir *redir;
	int in;
	int out;
	int pid;

	cmd = cmds->content;
	in = -1;
	out = -1;
	if (cmd->redirs)
	{
		redir = cmd->redirs->content;
		if (access(redir->filename, F_OK) == 0)
		{
			if (access(redir->filename, R_OK) == 0)
				in = open(redir->filename, O_RDONLY, 0444);
			/*else
				print_errors(3, NULL, file1);*/
		}
	}
	else
		dup2(in, STDIN_FILENO);
	for (int i = 0; i < ft_lstsize(cmds); i++)
	{
		dup2(in, 0);
		close(in);
		if (i == ft_lstsize(cmds) - 1)
		{
			if (cmd->redirs)
			{
				redir = cmd->redirs->content;
				out = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0622);
			}
			else
				out = dup(1);
		}
		else
		{
			pipe(pipe_fds);
			in = pipe_fds[0];
			out = pipe_fds[1];
		}
		dup2(out, 1);
		close(out);
		pid = fork();
		if (pid == 0)
			exec_cmd(cmds, envp);
		else
			wait(0);
		cmds = cmds->next;
	}	
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}	
