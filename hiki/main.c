#include "minishell.h"

void ll()
{
	system("leaks -q minishell");
}

void print_list(t_lexer *head)
{
	t_lexer *tmp;

	tmp = head;
	while (tmp != NULL)
	{
		printf("Current Node:\n");
		printf("Data: '%s'\n", tmp->data);
		printf("Type: %d\n", tmp->type);
		if (tmp->prev != NULL)
		{
			printf("Previous Node:\n");
			printf("Data: '%s'\n", tmp->prev->data);
		} 
		else
			printf("Previous Node: NULL\n");
		printf("--------------------------------\n");
		tmp = tmp->next;
	}   
}
void print_array(t_list *lst)
{
    t_list *temp = lst;

    while (temp != NULL)
	{
		int i = 0;
		printf("path = %s\n", temp->path_cmd);
        for (i = 0; temp->arr[i] != NULL; i++)
        {
            printf("|%s", temp->arr[i]);
        }
		printf("\n");

        printf("Number of Files: %d\n", temp->num_of_files);
		for (i = 0; i < temp->num_of_files; i++)
        {
            printf("\n--- File %d ---\n", i+1);
            printf("File Name: %s\n", temp->files[i].file_name);
            printf("File Type: %d\n", temp->files[i].type);
            printf("File Descriptor: %d\n", temp->files[i].fd);
        }

        printf("\n--- INFO ---\n");
        printf("Last Output Descriptor: %d\n", temp->out);
        printf("Last Input Descriptor: %d\n", temp->in);
        temp = temp->next;
    }
}

// void sig_handle(int sig)
// {
// 	(void) sig;
// 	g_status = 1;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void start_readline(t_lexer *lexer, t_list *lst, t_env *env, char **envr)
{
	char *line;

	while (1)
	{
		line = readline("\033[0;32mminishell[$]:\033[0m ");
		if (line == NULL)
			break;
		add_history(line);
		lexer = start_lexer(lexer, line);
		if (lexer != NULL && error_handler(lexer) != -1)
		{
			start_parsing(&lexer, env);
			if (lexer != NULL)
			{
				create_lst(&lst, &lexer, &env, envr);
				if (ft_exe(lst, env) == -1)
				{
					free_lst_lexer(&lexer);
					free_list(&lst);
				}
				else
				{
					free_lst_lexer(&lexer);
					lexer = NULL;
					free_list(&lst);
					lst = NULL;
				}
			}
			else
				g_status = 0;
		}
		else if (lexer != NULL)
		{
			free_lst_lexer(&lexer);
			lexer = NULL;
		}
	}
	free_lst_env(&env);
}

int main(int ac, char **av, char **envr)
{
	// atexit(ll);
	static t_lexer	*lexer;
	static t_list	*lst;
	static t_env 	*env;

	(void)ac;
	(void)av;
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, sig_handle);
	env_init(&env, envr);
	start_readline(lexer, lst, env, envr);
	// system("leaks -q minishell");
	return (g_status);
}
