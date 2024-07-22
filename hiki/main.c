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
		printf("var_quotes: %d\n", tmp->var_quotes);
		printf("len: %d\n", tmp->len);
		if (tmp->prev != NULL)
		{
			printf("Previous Node:\n");
			printf("Data: '%s'\n", tmp->prev->data);
		} 
		else
			printf("Previous Node: NULL\n");
		printf("--------------------------------\n");
		head = head->next;
		free(tmp->data);
		free(tmp);
	}   
}

int main(int ac, char **av, char **envr)
{
	atexit(ll);
	t_lexer	*head;
	t_env *env;
	char	*line;

	env_init(&env, envr);
	while ((line = readline("\033[0;32mminishell[$]:\033[0m ")) != NULL)
	{
		add_history(line);
		head = start_lexer(head, line);
		start_parsing(&head, env);
		print_list(head);
	}
	free_lst_env(&env);
	// system("leaks -q minishell")
}
