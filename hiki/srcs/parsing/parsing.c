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
	while(i <= ft_strlen(line))
	{
		if ((line[i] == ' ' || line[i] == '\0') && str[j - 1])
		{
			ft_lstadd_back(&head, ft_lstnew(str));
			ft_bzero(str, j);
			j = 0;
			i++;
		}
		else if (check_special_char(line + i) == true)
		{
			ft_lstadd_back(&head, ft_lstnew(str));
			ft_bzero(str, j);
			j = 0;
			i++;
		}
		if (line[i] != ' ')
		{
			str[j] = line[i];
			str[j + 1] = '\0';
			j++;
			i++;
		}
		else
			i++;
	}
	while (head)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
}
