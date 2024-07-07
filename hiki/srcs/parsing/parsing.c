#include "minishell.h"

bool check_special_char(char *str)
{
	int i;

	i = 0;
	// if (str[i] == '>' && str[i + 1] == '>')
	// 	return (true);=
	if (str[i] == '<' || str[i] == '>' )
	{
		return (true);
	}
	return (false);
}

void ft_start(t_list *head, char *line)
{
	int i;
	int j;
	char str[255];

	i = 0;
	j = 0;
	head = NULL;
	while(line[i])
	{
		if (check_special_char(line + i) == true)
		{
			str[j] = '\0';
			ft_lstadd_back(&head, ft_lstnew(str));
			printf("%s\n", head->data);
			ft_bzero(str, j);
			str[0] = line[i];
		}
		if (check_special_char(line + i) == true)
		{
			ft_lstadd_back(&head, ft_lstnew(str));
			printf("%s\n", head->data);
			ft_bzero(str, j);
			j = 0;
		} 
		str[j] = line[i];
		j++;
		i++;
	}
}
