
#include "exec.h"

void    parent_process(t_list **pids)
{
    int pid;

    while (*pids)
    {
        pid = *(int *)(*pids)->content;
        waitpid(pid, NULL, 0);
        *pids = (*pids)->next;
    }
}

void    child_process(t_cmd *cmd, char **envl, int (*pipes)[2], int nb_cmds)
{
    char    **to_ex;
    char    *path;

    if (pipes)
        close_pipes(pipes, nb_cmds);
    to_ex = lst_to_strs(cmd->tokens);
    if (!to_ex || !to_ex[0])
        return ;
    path = find_cmd_path(to_ex[0], envl);
    if (execve(path, to_ex, envl) == -1)
        return ;
}