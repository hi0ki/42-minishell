#include "minishell.h"

/*

example
	var="ls -a"
	inpute : $var fhad case kahsni nspliti b space and quotes
	inpute2 : ls $var hna khasni nspliti ha b space hna fach anhandli ambiguous redirect

*/

void set_variable_value(t_lexer **node, t_env *env)
{
	char *str;
	int j;

	j = (*node)->var_quotes;
	while ((*node)->data[j] && (*node)->data[j] != ' ')
		j++;
	str = ft_substr((*node)->data, (*node)->var_quotes, j - (*node)->var_quotes);
	printf(">>>>>>>>>>>>>>>>> %s\n", str);
}
void check_var_quotes(t_lexer **head, t_env *env)
{
	t_lexer *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == SQUOTE || tmp->type == DQUOTE)
		{
			int i = 0;
			while (tmp->data[i])
			{
				if (tmp->data[i] == '$')
				{
					tmp->var_quotes = i;
					set_variable_value(&tmp, env);
					break;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void start_parsing(t_lexer **head, t_env *env)
{
	check_var_quotes(head, env);
}