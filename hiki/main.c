#include "minishell.h"

void ll()
{
	system("leaks -q minishell");
}

void print_list(t_lexer *head)
{
	t_lexer *tmp;

	while (head != NULL)
	{
		tmp = head;
		printf("Current Node:\n");
		printf("Data: '%s'\n", tmp->data);
		printf("Type: %d\n", tmp->type);
		if (tmp->prev != NULL)
		{
			printf("Previous Node:\n");
			printf("Data: '%s'\n", tmp->prev->data);
			printf("Type: %d\n", tmp->prev->type);
		} 
		else
			printf("Previous Node: NULL\n");
		printf("--------------------------------\n");
		head = head->next;
		free(tmp->data);
		free(tmp);
	}   
}

int main()
{
	atexit(ll);
	t_lexer	*head;
	char	*line;

	while ((line = readline("minishell $> ")) != NULL)
	{
		add_history(line);
		head = ft_start(head, line);
		print_list(head);   
	}
	// system("leaks -q minishell")
}
