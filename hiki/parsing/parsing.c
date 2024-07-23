#include "minishell.h"

/*

example
	var="ls -a"
	inpute : $var fhad case kahsni nspliti b space and quotes
	inpute2 : ls $var hna khasni nspliti ha b space hna fach anhandli ambiguous redirect

*/


void start_parsing(t_lexer **head, t_env *env)
{
	t_lexer *tmp;

	fill_variables(head, env);
	// tmp = *head;
	join_nodes(head);
}

/*

 echo path=$PATH hada kahsni ngado

*/