#include "minishell.h"

void fill_arr(t_list **lst, t_lexer **head, int size)
{
	t_lexer *tmp;
	t_list  *lstmp;
	int i;

	if (!*lst)
		return ;
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
				if (tmp->type >= 5 && tmp->type <= 8)
					tmp = tmp->next->next;
				else
				{
					lstmp->arr[i] = ft_strdup(tmp->data);
					tmp = tmp->next;
					i++;
				}
			}
			lstmp->arr[i] = NULL;
			lstmp = lstmp->next;
			while (tmp && tmp->type != PIPE)
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}