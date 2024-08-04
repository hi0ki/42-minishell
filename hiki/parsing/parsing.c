#include "minishell.h"

void split_env_var(t_lexer **head)
{
	t_lexer *tmp;
	char	 *save;
	t_lexer *node;
	int		i;
	char **arr;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == DOLLAR)
		{
			arr = ft_split(tmp->data, " \t");
			save = tmp->data;
			i = 0;
			while (arr[i])
			{
				if (i == 0)
					tmp->data = ft_strdup(arr[0]);
				else
				{
					node = lexer_lstnew(ft_strdup(arr[i]));
					node->next = tmp->next;
					node->type = WORD;
					if (tmp->next)
						tmp->next->prev = node;
					node->prev = tmp;
					tmp->next = node;
					tmp = tmp->next;
				}
				tmp->len = ft_strlen(arr[i]);
				tmp->type = WORD;
				free(arr[i]);
				i++;
			}
			free(arr);
			free(save);
		}
		tmp = tmp->next;
	}
}
void start_parsing(t_lexer **head, t_env *env)
{
	fill_variables(head, env);
	join_nodes(head);
	split_env_var(head);
	parsing_type(head);
}
