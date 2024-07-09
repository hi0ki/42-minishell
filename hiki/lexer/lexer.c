#include "minishell.h"

t_list *ft_start(t_list *head, char *line)
{
	char	*str;
	int		i;
	int		index;

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
		}
		else if (check_special_char(line + i) == 3)
		{
			str = ft_str_alloc(line + i + 1, ft_handle_quotes(line + i));
			ft_lstadd_back(&head, ft_lstnew(str));
			i += ft_handle_quotes(line + i) + 1;
		}
		else if (check_special_char(line + i) > 0)
		{
			str = alloc_special_char(line + i);
			ft_lstadd_back(&head, ft_lstnew(str));
			i += check_special_char(line + i);
		}
		else
			i++;
	}
	free(line);
	return (head);
}
