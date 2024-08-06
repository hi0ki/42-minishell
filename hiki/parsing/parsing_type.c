#include "minishell.h"

void remove_spaces(t_lexer **head)
{
	t_lexer *tmp;
	t_lexer *save;

	tmp = *head;
	// while ((*head))
	// {
	// 	printf("data = %s|type = %d\n", (*head)->data, (*head)->type);
	// 	(*head) = (*head)->next;
	// }
	while (tmp)
	{
		if (tmp->type == SPACE)
		{
			save = tmp;
			tmp = tmp->prev;
			if (tmp->next->next != NULL)
			{
				tmp->next = tmp->next->next;
				tmp->next->prev = tmp;
			}
			else
				tmp->next = NULL;
			free(save->data);
			free(save);
		}
		tmp = tmp->next;
	}
}
void give_type(t_lexer **node)
{
	if ((*node)->type >= 5 && (*node)->type <= 8)
		return ;
	else if ((*node)->prev == NULL || ft_strcmp((*node)->prev->data, "|") == 0)
		(*node)->type = CMD;
	else if (ft_strcmp((*node)->data, "|") == 0)
		(*node)->type = PIPE;
	else
		(*node)->type = ARG;
}

void parsing_type(t_lexer **head)
{
	t_lexer *tmp;

	remove_spaces(head);
	tmp = *head;
	while (tmp)
	{
		give_type(&tmp);
		tmp = tmp->next;
	}
}