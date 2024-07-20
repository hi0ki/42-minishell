#include "minishell.h"


void free_lst_lexer(t_lexer **head)
{
	t_lexer *tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->data);
		free((*head));
		*head = tmp;
	}
}