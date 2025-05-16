/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpramann <vpramann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 06:51:03 by marykman          #+#    #+#             */
/*   Updated: 2025/05/16 18:28:40 by vpramann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	print_token(void *content)
{
	char	*token;

	if (!content)
		return ;
	token = content;
	ft_printf("token: `%s`\n", token);
}

static void	print_redir(void *content)
{
	t_redir	*redir;

	if (!content)
		return ;
	redir = content;
	ft_printf("redir: %d\tfilename: %s\n", redir->type, redir->filename);
}

static void	print_cmd(void *content)
{
	t_cmd	*cmd;
	
	if (!content)
		return ;
	cmd = content;
	ft_printf("=== New command: ===\n");
	ft_lstiter(cmd->tokens, &print_token);
	ft_lstiter(cmd->redirs, &print_redir);
	ft_printf("====================\n\n");
}

void check_exit_status(pid_t pid)
{
    int status;

    // Wait for the child process to finish
    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        return;
    }

    // Check if the process exited normally
    if (WIFEXITED(status))
    {
        int exit_code = WEXITSTATUS(status);
        printf("Process exited with status: %d\n", exit_code);
    }
    // Check if the process was terminated by a signal
    else if (WIFSIGNALED(status))
    {
        int signal = WTERMSIG(status);
        printf("Process terminated by signal: %d\n", signal);
    }
    // Check if the process was stopped by a signal
    else if (WIFSTOPPED(status))
    {
        int signal = WSTOPSIG(status);
        printf("Process stopped by signal: %d\n", signal);
    }
}
