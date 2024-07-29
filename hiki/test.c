#include "minishell.h"

void shell(t_list **lst, char **env)
{
	if (execve((*lst)->path_cmd, (*lst)->arr, env) == -1) {
        perror("execve failed");
    }
}