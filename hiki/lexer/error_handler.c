#include "minishell.h"

int error_handler(t_lexer *lexer)
{
	int status;
	t_lexer *tmp;

	status = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->error_quotes == -1)
		{
			ft_putstrn_fd("minishell: syntax error: no end of quotes", 2);
			g_status = 258;
			return (-1);
		}
		else if (tmp->type == PIPE && (tmp->prev == NULL || tmp->next == NULL))
		{
			ft_putstrn_fd("minishell: syntax error", 2);
			g_status = 258;
			return (-1);
		}
		else if ((tmp->type == REDIRECT_INPUT || tmp->type  == HEREDOC) )
		{
			ft_putstrn_fd("minishell: syntax error files", 2);
			g_status = 258;
			return (-1);
		}
		// printf("type->%d\n", tmp->type);
		tmp = tmp->next;
	}
	return	(0);
}