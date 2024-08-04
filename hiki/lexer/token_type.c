#include "minishell.h"

/*

khsni nchecki kola data fiha bach n3rf ach khas it3tahom

*/

/*

nhandly dak lblan dyal double qoates 
ila malgitch space njm3 dakchi li morah nichan


*/

static int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (s2 == NULL)
		return (2);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (i != ft_strlen(s1) || i != ft_strlen(s2))
		return (-1);
	return (0);
}

void set_type(t_lexer **node)
{
	if (!_strcmp(" ", (*node)->data))
		(*node)->type = SPACE;
	else if (!_strcmp("\t", (*node)->data))
		(*node)->type = SPACE;
	else if (!_strcmp("|", (*node)->data))
		(*node)->type = PIPE;
	else if (!_strcmp("<", (*node)->data))
		(*node)->type = REDIRECT_INPUT;
	else if (!_strcmp(">", (*node)->data))
		(*node)->type = REDIRECT_OUTPUT;
	else if (!_strcmp(">>", (*node)->data))
		(*node)->type = REDIRECT_APPEND;
	else if (!_strcmp("<<", (*node)->data))
		(*node)->type = HEREDOC;
	else if ((*node)->data[0] == '$')
		(*node)->type = DOLLAR;
	else
		(*node)->type = WORD;
	(*node)->len = ft_strlen((*node)->data);
}