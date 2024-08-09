#include "minishell.h"

int check_oper(t_lexer *node)
{
	if (node->type >= 5 && node->type <= 8)
		return (0);
	return (1);
}