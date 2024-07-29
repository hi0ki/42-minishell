#include "minishell.h"

void fill_arr(t_list **lst, t_lexer **head, int size)
{
	t_lexer *tmp;
	t_list  *lstmp;
	int i;

	lstmp = *lst;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type != PIPE)
		{
			size = count_cmd(tmp);
			lstmp->arr = malloc((size + 1) * sizeof(char *));
			i = 0;
			while (i < size)
			{
				lstmp->arr[i] = ft_strdup(tmp->data);
				tmp = tmp->next;
				i++;
			}
			lstmp->arr[i] = NULL;
			lstmp = lstmp->next;
		}
		else
			tmp = tmp->next;
	}
}

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
	while(array[i])
	{
		if (access((*node)->arr[0], F_OK) == 0)
		{
			(*node)->path_cmd = ft_strdup((*node)->arr[0]);
			return ;
		}
		path = join_path(array[i], (*node)->arr[0]);
		if (access(path, F_OK) == 0)
		{
			(*node)->path_cmd = ft_strdup(path);
			free(path);
			return ;
		}
		free(path);
		i++;
	}
	(*node)->path_cmd = NULL;
}

void fill_path(t_list **lst, t_env *env)
{
	char **array;
	char *str;
	t_list *tmp;

	int i = 0;
	tmp = *lst;
	str = get_value_env(env, "PATH");
	array = ft_split(str, ':');
	while (tmp)
	{
		check_path(&tmp, array);
		tmp = tmp->next;
	}
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	free(str);
}

void create_lst(t_list **lst, t_lexer **head, t_env **env)
{
	int size;
	int i;
	
	*lst = NULL;
	size = size_node(*head);
	while (size > 0)
	{
		ft_lstadd_back(lst, ft_lstnew());
		size--;
	}
	fill_arr(lst, head, size);
	fill_path(lst, *env);
}