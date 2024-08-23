#include "minishell.h"

void ll()
{
	system("leaks -q minishell");
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
				if (ft_exe(lst) == -1)
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
