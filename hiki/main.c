#include "minishell.h"

void ll()
{
	system("leaks -q minishell");
}

int main()
{
	atexit(ll);
	t_list	*head;
	char	*line;
	t_list *tmp;

	while ((line = readline("minishell $> ")) != NULL)
	{
		head = ft_start(head, line);
		while (head != NULL)
		{
   	 		tmp = head;
   	 		printf("%s\n", tmp->data); // Assuming 'data' is the name of the data field in your list node
  	  		head = head->next;
  	  		free(tmp->data);
  	  		free(tmp);
		}
	}
	// system("leaks -q minishell")

}