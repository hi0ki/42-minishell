#include "minishell.h"

char *join_path(char *arr, char *cmd)
{
	char *tmp;
	char *str;
	tmp = ft_strjoin(arr, "/");
	str = ft_strjoin(tmp, cmd);
	free(tmp);
	return str;
}

void check_path(t_list **node, char **array)
{
    int i;
    char *path;

    i = 0;
    if (!(*node)->arr[0])
    {
        (*node)->path_cmd = NULL;
        return ;
    }
    while(array[i] && ft_strlen((*node)->arr[0]) != 0)
    {
        path = join_path(array[i], (*node)->arr[0]);
        if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
        {
            (*node)->path_cmd = ft_strdup(path);
            free(path);
            return ;
        }
        free(path);
        path = NULL;
        i++;
    }
    if (path == NULL && access((*node)->arr[0], F_OK) == 0 && access((*node)->arr[0], X_OK) == 0)
    {
		(*node)->path_cmd = ft_strdup((*node)->arr[0]);
		return ;
    }
    (*node)->path_cmd = NULL;
}

void fill_path(t_list **lst, t_env **env, char **envr)
{
	char **array;
	char *str;
	t_list *tmp;

	int i = 0;
	tmp = *lst;
	str = get_value_env(*env, "PATH");
	if (str)
		array = ft_split(str, ":");
	while (tmp)
	{
		if (str)
			check_path(&tmp, array);
		else
		{
			tmp->path_cmd = NULL;
			// tmp->arr = NULL;
		}
		tmp->envr = envr;
<<<<<<< HEAD
		// tmp->env = &env;
=======
		tmp->env = env;
>>>>>>> f42f77d33c9d0d30b4a53e59f2540b5fc0c2f5fe
		tmp = tmp->next;
	}
	if (str)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
		free(str);
	}
}
