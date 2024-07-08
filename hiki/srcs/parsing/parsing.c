#include "minishell.h"


/*

	wlit m7taj hir {'' & ""};
	hadchi li mhtaj daba

*/

int check_special_char(char *str)
{
	int i;

	i = 0;
	if ((str[i] == '>' && str[i + 1] == '>') || 
		(str[i] == '<' && str[i + 1] == '<'))
		return (2);
	if (str[i] == '<' || str[i] == '>' || str[i] == ' ' || 
		str[i] == '|')
	{
		return (1);
	}
	return (0);
}

char *alloc_special_char(char *line)
{
	char *str;
	int	i;
	int type;

	i = 0;
	type = check_special_char(line + i);
	str = malloc((type + 1) * sizeof(char));
	if (type == 1)
	{
		str[i] = line[i];
		i++;
	}
	else if (type == 2)
	{
		while (i < type)
		{
			str[i] = line[i];
			i++;
		}
	}
	str[i] = '\0';
	return str;
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
	while (i < ft_strlen(line))
	{
		i += index;
		index = get_index(line + i, " ><|");
		if (index != 0)
		{
			str = ft_str_alloc(line + i, index);
			ft_lstadd_back(&head, ft_lstnew(str));
			free(str);
		}
		else if (check_special_char(line + i) > 0)
		{

			str = alloc_special_char(line + i);
			ft_lstadd_back(&head, ft_lstnew(str));
			free(str);
			i += check_special_char(line + i);
		}
	}
	return (head);
}



