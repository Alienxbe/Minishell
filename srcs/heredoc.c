/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:11:30 by marykman          #+#    #+#             */
/*   Updated: 2025/06/06 22:49:08 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_string.h"
#include "ft_list.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "exec.h"
#include "expander.h"
#include "parsing.h"
#include "minishell.h"

static void	heredoc_loop(t_redir *redir)
{
	char	*line;

	line = NULL;
	while (true)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->filename))
			break ;
		add_element(&redir->heredoc, line);
	}
	if (line)
		free(line);
}

static void	loop_redir(void *content, void *param)
{
	t_redir	*redir;
	t_list	*lst;

	if (!content || !param)
		return ;
	redir = content;
	if (redir->type != REDIR_HEREDOC)
		return ;
	heredoc_loop(content);
	lst = redir->heredoc;
	while (lst)
	{
		lst->content = expand(lst->content, param);
		lst = lst->next;
	}
}

static void	loop_cmd(void *content, void *param)
{
	t_cmd	*cmd;
	t_msh	*msh;

	if (!content)
		return ;
	cmd = content;
	msh = param;
	ft_lstiterp(cmd->redirs, loop_redir, msh);
}

void	heredoc(t_list *cmds, t_msh *msh)
{
	ft_lstiterp(cmds, loop_cmd, msh);
}
