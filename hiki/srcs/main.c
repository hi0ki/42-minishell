#include "minishell.h"

/*

khasni n9sm cmd o n7to f list achno ba9i lah w3lm

*/

int main()
{
	t_list *head;
	char *line;

		while ((line = readline("minishell $> ")) != NULL)
		{
			ft_start(head, line);
		}
	printf("howa\n");
	while(head)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
}