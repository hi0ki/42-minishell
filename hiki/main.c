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
		printf("howa %d\n", temp->num_of_files);
		for (i = 0; i < temp->num_of_files; i++)
		{
			printf("File name: %s\n", file[i].file_name);
			printf("File type: %d\n", file[i].type);
			printf("File type: %d\n", file[i].fd);
		}
		printf("file last in %s\n", temp->last_infile);
		printf("file last out %s\n", temp->last_outfile);
		printf("last out %d\n", temp->out);
		printf("last in %d\n", temp->in);
        temp = temp->next;
    }
}

int main(int ac, char **av, char **envr)
{
	// atexit(ll);
	t_lexer	*lexer;
	t_list	*lst;
	t_env 	*env;
	char	*line;

	(void)ac;
	(void)av;
	env_init(&env, envr);
	while ((line = readline("\033[0;32mminishell[$]:\033[0m ")) != NULL)
	{
		add_history(line);
		lexer = start_lexer(lexer, line);
		if (lexer != NULL && error_handler(lexer) != -1)
		{
			start_parsing(&lexer, env);
			create_lst(&lst, &lexer, &env, envr);
			if (ft_exe(lst, env) == -1)
			{
				free_lst_lexer(&lexer);
				free_list(&lst);
			}
			// print_array(lst);
			// print_list(lexer);
			// free_list(&lst);
			// free_lst_lexer(&lexer);

		}
		else if (lexer != NULL)
		{
			free_lst_lexer(&lexer);
		}
	}
	free_lst_env(&env);
	// // system("leaks -q minishell")
	return (g_status);
}
