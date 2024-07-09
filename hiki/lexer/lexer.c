#include "minishell.h"

int ft_handle_quotes(char *line)
{
	int i;
	char c;

	i = 0;
	if	(line[i] == '\'')
		c = '\'';
	if (line[i] == '\"')
		c = '\"';
	i++;
	while (line[i] && line[i] != c)
		i++;
	return (i - 1);
}

t_list *ft_start(t_list *head, char *line)
{
	char	*str;
	int		i;
	int		index;
	int		type;

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
			ft_lstadd_back(&head, ft_lstnew(str));
			free(str);
		}
		else if (check_special_char(line + i) == 3)
		{
			str = ft_str_alloc(line + i + 1, ft_handle_quotes(line + i));
			ft_lstadd_back(&head, ft_lstnew(str));
			free(str);
			i += ft_handle_quotes(line + i) + 1;
		}
		else if (check_special_char(line + i) > 0)
		{
			str = alloc_special_char(line + i);
			ft_lstadd_back(&head, ft_lstnew(str));
			free(str);
			i += check_special_char(line + i);
		}
		else
			i++;
	}
	free(line);
	return (head);
}
