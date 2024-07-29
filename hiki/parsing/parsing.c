#include "minishell.h"

void start_parsing(t_lexer **head, t_env *env)
{
	fill_variables(head, env);
	join_nodes(head);
	parsing_type(head);
}
