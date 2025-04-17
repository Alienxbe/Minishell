/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:39:58 by vpramann          #+#    #+#             */
/*   Updated: 2025/03/14 22:40:30 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>
#include "ft_memory.h"
#include "../../includes/exec.h"
#include "../../includes/env.h"

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

static char	*find_path(char **paths, char **cmds, int i)
{
	char	*path;
	char	*cmdpath;

	path = ft_strjoin(paths[i], "/");
	cmdpath = ft_strjoin(path, cmds[0]);
	if (access(cmdpath, F_OK | X_OK) == 0)
		return (free(path), cmdpath);
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
	return (NULL);
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

void exec_cmdtmp(t_list *cmds, char **envp)
{
    char	**cmdss;
	char	*path;

	if (!envp)
		return ;
	cmdss = find_cmds(cmds);
	path = find_cmd_path(cmdss[0], envp);
	if (execve(path, cmdss, envp) == -1)
	{
		free(path);
		free_tab(cmdss);
		return ;
	}
	free(path);
	free_tab(cmdss);
}

/*void exec_cmdstmp(t_list *cmds, char ** envp)
{
	t_cmd *cmd;
	int pipe_fds[2];
	t_redir *redir;
	int in;
	int out;
	pid_t pid;

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
			//else
				//print_errors(3, NULL, file1);
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
			wait(NULL);
		cmds = cmds->next;
	}	
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}*/


static int	(*init_pipes(t_list *cmds))[2]
{
	int	(*pipes)[2];
	int	pipe_count;
	int	i;

	pipe_count = ft_lstsize(cmds);
	if (pipe_count < 2)
		return (NULL);
	pipes = ft_calloc(pipe_count, sizeof(int[2]));
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < pipe_count - 1)
	{
		if (pipe(pipes[i]) < 0)
		{
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			free(pipes);
			return (NULL);	// TODO: free
		}
	}	
	return (pipes);
}

static void	set_pipes(int cmd_index, int (*pipes)[2], int nb_cmds)
{
	/*t_redir *pot_file;
	t_redir_type red_type;
	int fd;
	
	// if redir_file
	pot_file = redir->content;
	red_type = 0;
	fd = -1;
	if (pot_file->filename)
	{
		if (pot_file->type)
			red_type = pot_file->type;
		if (red_type == REDIR_STDIN)
		{
			if (access(pot_file->filename, F_OK) == 0)
			{
				if (access(pot_file->filename, R_OK) == 0)
					fd = open(pot_file->filename, O_RDONLY, 0444);
			else
				print_errors(3, NULL, file1);
			}
			if (fd == -1)
				exit (1);
			dup2(fd, STDIN_FILENO);
			dup2(pipes[0][1], STDOUT_FILENO);	
		}
		else if (red_type == REDIR_STDOUT)
		{
			
		}
	}*/
	// else redir pipe
	if (cmd_index != 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index != nb_cmds - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	
}


static void exec(t_cmd *cmd, char **envl)
{
	char	**to_ex;
	char	*path;
	int		pid;
	
	//if (isbuiltin(tcmd))
	// ftbuiltin
	to_ex = lst_to_strs(cmd->tokens);
	if (!to_ex || !to_ex[0])
	{
		free_tab(to_ex);
		return ;
	}
	path = find_cmd_path(to_ex[0], envl);
	pid = fork();
	if (pid == -1)
	{
		free(path);
		free_tab(to_ex);
		free_tab(envl);
		return ;
	}
	if (pid == 0)
	{
		if (execve(path, to_ex, envl) == -1)
		{
			free(path);
			free_tab(to_ex);
			free_tab(envl);
			exit(1);
		}
	}
	else
		waitpid(pid, NULL, 0);
}

static void	exec_cmd(t_cmd *cmd,int cmd_index, t_list *envl, int nb_cmds)
{
	int	saved_io[2];
	char	**envc;

	
	(void)envl;
	saved_io[0] = dup(STDIN_FILENO);
	saved_io[1] = dup(STDOUT_FILENO);
	envc = lst_to_strs(envl);
	// Setup pipes (redirect or pipe) -> set stdin/out
	set_pipes(cmd_index, &saved_io, nb_cmds);
	// Exec (builtins or not)
	exec(cmd, envc);
	dup2(saved_io[0], STDIN_FILENO);
	dup2(saved_io[1], STDOUT_FILENO);
	close(saved_io[0]);
	close(saved_io[1]);
}

void	exec_cmds(t_list *cmds, t_list *envl)
{
	t_list	*lst;
	int		(*pipes)[2];
	int		i;
	int 	nb_cmds;

	(void)envl;
	nb_cmds = ft_lstsize(cmds);
	pipes = init_pipes(cmds);
	// Loop exec
	lst = cmds;
	i = 0;
	while (lst)
	{
		exec_cmd(lst->content, i++, envl, nb_cmds);
		lst = lst->next;
	}
	free(pipes);
}