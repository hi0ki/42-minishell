#include "minishell.h"

int main()
{
	t_list	*head;
	char	*line;

	while ((line = readline("minishell $> ")) != NULL)
	{
		head = ft_start(head, line);
	}
	// system("leaks -q minishell");
	while (head)
	{
		printf(">>%s\n", head->data);
		head = head->next;
	}
}