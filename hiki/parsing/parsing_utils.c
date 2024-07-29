#include "minishell.h"

int size_node(t_lexer *head)
{
	int i;

	i = 1;
	while (head)
	{
		if (head->type == PIPE)
			i++;
		head = head->next;
	}
	return (i);
}

int count_cmd(t_lexer *head)
{
	int i;

	i = 0;
	while(head && head->type != PIPE)
	{
		i++;
		head = head->next;
	}
	return i;
}
