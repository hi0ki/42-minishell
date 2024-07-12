#include "minishell.h"

t_lexer *ft_start(t_lexer *head, char *line)
{
	char	*str;
	int		i;
	int		index;
	int		test;

	i = 0;
	index = 0;
	head = NULL;
	while (line[i])
	{
		i += index;
		index = get_index(line + i, " \"'><|");
		if (index != 0)
		{
			str = ft_str_alloc(line + i, index);
			lexer_add_back(&head, lexer_lstnew(str));
		}
		else if (check_special_char(line + i) == 3)
		{
			test = ft_handle_quotes(line + i);
			if (test != 0)
			{
				str = ft_str_alloc(line + i + 1, test);
				lexer_add_back(&head, lexer_lstnew(str));
				i += test + 1;
			}
			else
				i++;
		}
		else if (check_special_char(line + i) > 0)
		{
			str = alloc_special_char(line + i);
			lexer_add_back(&head, lexer_lstnew(str));
			i += check_special_char(line + i);
		}
		else
			i++;
	}
	free(line);
	return (head);
}
