
#include "exec.h"

void    parent_process(t_list **pids)
{
    long pid;
    t_list *tmp;

    if (!pids || !*pids)
        return ;
    tmp = *pids;
    while (tmp)
    {
        if (!tmp->content)
            return ;
        pid = *(long *)(tmp);
        waitpid(pid, NULL, 0);
        tmp = tmp->next;
    }
}

void    child_process(t_cmd *cmd, char **envc, int (*pipes)[2], int nb_cmds)
{
    char    **to_ex;
    char    *path;

    close_pipes(pipes, nb_cmds);
    to_ex = lst_to_strs(cmd->tokens);
   if (!to_ex || !to_ex[0])
        return ;
    if (has_absolute_path(to_ex[0]) || has_relative_path(to_ex[0]))
    {
        if (access(to_ex[0], F_OK | X_OK) == 0)
            path = ft_strdup(to_ex[0]);
        else
        {
            printf("minishell: %s: command not found\n", to_ex[0]);
            free_tab(to_ex);
            free_tab(envc);
            exit(127);
        }
    }
    else
        path = find_cmd_path(to_ex[0], envc);
    if (execve(path, to_ex, envc) == -1)
    {
        perror("execve");
        free(path);
        free_tab(to_ex);
        free_tab(envc);
        exit(1);
    }
    free(path);
    free_tab(to_ex);
    free_tab(envc);
    exit(0);
}