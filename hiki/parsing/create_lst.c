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

void fill_path(t_list **lst, t_env *env, char **envr)
{
	char **array;
	char *str;
	t_list *tmp;

	int i = 0;
	tmp = *lst;
	str = get_value_env(env, "PATH");
	array = ft_split(str, ":");
	while (tmp)
	{
		check_path(&tmp, array);
		tmp->env = envr;
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
void	num_of_files(t_list **lst, t_lexer **lexer)
{
	t_list *tmp;
	t_lexer *lextmp;
	int i;

	i = 0;
	tmp = *lst;
	lextmp = *lexer;
	while (lextmp && tmp)
	{
		if (lextmp->type == PIPE)
		{
			tmp->num_of_files = i;
			i = 0;
			tmp = tmp->next;
			lextmp = lextmp->next;
		}
		if (lextmp->type == HEREDOC || lextmp->type == REDIRECT_APPEND || lextmp->type == REDIRECT_INPUT || lextmp->type == REDIRECT_OUTPUT)
		{
			i++;
		}
		lextmp = lextmp->next;
	}
	if (lextmp == NULL && tmp != NULL)
		tmp->num_of_files = i;
}

void fill_files(t_list **lst, t_lexer **lexer)
{
	t_list *tmp;
	t_lexer *lextmp;
	int i;

	tmp = *lst;
	lextmp = *lexer;
	tmp->files = malloc (tmp->num_of_files * sizeof(t_files));
	i = 0;
	while (lextmp && tmp)
	{
		if (lextmp->type == PIPE)
		{
			tmp = tmp->next;
			i = 0;
			tmp->files = malloc (tmp->num_of_files * sizeof(t_files));
		}
		if (lextmp->type >= 5 && lextmp->type <= 8)
		{
			tmp->files[i].type = lextmp->type;
			tmp->files[i].fd = open(lextmp->next->data, O_CREAT | O_RDWR, 0777);
			if (tmp->files[i].fd == -1)
			{
				printf("error\n");
				exit(9);
			}
			tmp->files[i].file_name = ft_strdup(lextmp->next->data);
			lextmp = lextmp->prev;
			lextmp->next = lextmp->next->next->next;
			lextmp->next->prev = lextmp;
			i++;
		}
		lextmp = lextmp->next;
	}
}
void create_lst(t_list **lst, t_lexer **head, t_env **env, char **envr)
{
	int size;
	
	*lst = NULL;
	size = size_node(*head);
	while (size > 0)
	{
		ft_lstadd_back(lst, ft_lstnew());
		size--;
	}
	num_of_files(lst, head);
	fill_files(lst, head);
	fill_arr(lst, head, size);
	fill_path(lst, *env, envr);
}