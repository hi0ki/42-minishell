#include "minishell.h"

void remove_spaces(t_lexer **head)
{
	t_lexer *tmp;
	t_lexer *save;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == SPACE)
		{
			save = tmp;
			tmp = tmp->prev;
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
			free(save->data);
			free(save);
		}
		tmp = tmp->next;
	}
}
void give_type(t_lexer **node)
{
	if ((*node)->prev == NULL || ft_strcmp((*node)->prev->data, "|") == 0)
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