#include "minishell.h"

void ll()
{
	// system("leaks -q minishell");
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
void print_array(t_list *lst)
{
    t_list *temp = lst;

    while (temp != NULL)
	{
		int i = 0;
		printf("path = %s\n", temp->path_cmd);
		while (temp->arr[i] != NULL)
		{
			printf("|%s |", temp->arr[i]);
			i++;
		}
		printf("\n");
		t_files *file = temp->files;
		for (i = 0; i < temp->num_of_files; i++)
		{
			printf("File name: %s\n", file[i].file_name);
			printf("File type: %d\n", file[i].type);
			printf("File type: %d\n", file[i].fd);
		}
        temp = temp->next;
    }
}

int main(int ac, char **av, char **envr)
{
	atexit(ll);
	t_lexer	*lexer;
	t_list	*lst;
	t_env 	*env;
	char	*line;

	// char **arr = ft_split("mehdi\thowa ana", " \t");
	(void)ac;
	(void)av;
	env_init(&env, envr);
	while ((line = readline("\033[0;32mminishell[$]:\033[0m ")) != NULL)
	{
		add_history(line);
		lexer = start_lexer(lexer, line);
		if (lexer != NULL)
		{
			start_parsing(&lexer, env);
			create_lst(&lst, &lexer, &env, envr);
			ft_exe(lst, env);
			// print_list(lexer);
			print_array(lst);


			// free_lst_lexer(&lexer);
			// free_list(&lst);
		}
	}
	free_lst_env(&env);
	// // system("leaks -q minishell")
}
