#include "minishell.h"

static	t_lexer	*get_node(char *line, int i, int index, int type)
{
	char	*str;
	int 	helper;
	t_lexer *node;

	if (type == 0)
		str = ft_str_alloc(line + i, index);
	else if (type == 1)
	{
		if (line[i] == '\'')
			helper = SINGLE_QUOTE;
		else if (line[i] == '\"')
			helper = DOUBLE_QUOTE;
		str = ft_str_alloc(line + i + 1, index - 1); // hna drt + 1 bach nfot qoute >' or "< o n9st 1 bach manwslch liha nakhd string li binathom safi
		node = lexer_lstnew(str);
		node->type = helper;
		return node;
	}
	else if (type == 2)
		str = alloc_special_char(line + i);
	node = lexer_lstnew(str);
	set_type(&node);
	return node;
}


t_lexer *ft_start(t_lexer *head, char *line)
{
	char	*str;
	int		i;
	int		index;
	int		nbr;

	i = 0;
	index = 0;
	nbr = 0;
	if (ft_strlen(line) == 0)
		return (NULL);
	head = NULL;
	line = ft_strtrim(line, " ");
	while (line[i])
	{
		index = get_index(line + i, " \"'><|");
		if (index != 0)
		{
			lexer_add_back(&head, get_node(line, i, index, 0));
			i += index;
		}
		else if (check_special_char(line + i) == 3)
		{
			nbr = ft_handle_quotes(line + i); // FACH AY3TINI ''
			if (nbr == -1)
				return (printf("\033[31mError\n\033[0m"), NULL); // khasni nzid lfree dyal dakchi li kan f head
			lexer_add_back(&head, get_node(line, i, nbr, 1));
			i += nbr + 1; // hna zdt 1 bach nfot > qoutes '"<
		}
		else if (check_special_char(line + i) > 0)
		{
			nbr = check_special_char(line + i);
			lexer_add_back(&head, get_node(line, i, index, 2));
			i += nbr;
			while(line[i] == ' ') // to skip spaces bc we just one
				i++;
		}
		else
			i++;
	}
	free(line);
	return (head);
}
