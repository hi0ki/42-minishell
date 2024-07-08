#include "minishell.h"

/*

khasni n9sm cmd o n7to f list achno ba9i lah w3lm

*/

// void print_list(t_list *head)
// {
// 	while (head)
// 	{
// 		printf("%s\n", head->data);
// 		head = head->next;
// 	}
// }

int main()
{
	t_list	*head;
	char	*line;

	while ((line = readline("minishell $> ")) != NULL)
	{
		head = ft_start(head, line);
	}
	while (head)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
}