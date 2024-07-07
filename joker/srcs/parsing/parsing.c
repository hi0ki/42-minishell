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

void	skip_spaces(char *str)
{
	int i = 0;

	while (*str && *str == ' ')
		*str++;
}

void ft_start(t_list *head, char *line)
{
	int		i = 0;
	int		cnt = 0;	
	char	*str;
	// t_list	*head;
	// t_list  *nd;
	int     k;
	// head = NULL;
	while(line[i])
	{
		// if (check_special_char(line + i) == true)
		// {
		// 	str[j] = '\0';
		// 	ft_lstadd_back(&head, ft_lstnew(str));
		// 	printf("%s\n", head->data);
		// 	ft_bzero(str, j);
		// 	str[0] = line[i];
		// }
		// if (check_special_char(line + i) == true)
		// {
		// 	ft_lstadd_back(&head, ft_lstnew(str));
		// 	printf("%s\n", head->data);
		// 	ft_bzero(str, j);
		// 	j = 0;
		// } 
		// str[j] = line[i];
		// j++;
		// i++;
		skip_spaces(line);
		k = i;
			printf("%d\n", i);
			cnt = 0; 
			while (line[i] && line[i] != '<' && line[i] != '>' && \
				 line[i] != '|')
			{
				cnt++;
				i++;
			}
			printf("%d\n", i);
			str = malloc(cnt + 1);
			i = k;
			cnt = 0;
			while (line[i] && line[i] != '<' && line[i] != '>' && \
				 line[i] != '|')
			{
				str[cnt] = line[i];
				cnt++;
				i++;
			}
			printf("%d\n", i);
			str[cnt] = '\0';
			// nd = ft_lstnew(str);
			// printf("%s\n", nd->data);
			ft_lstadd_back(&head, ft_lstnew(str));
			free(str);
			if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				str = malloc(2);
				str[0] = line[i];
				str[1] = '\0';
				i++;
				// nd = ft_lstnew(str);
				// printf("%s\n", nd->data);
				ft_lstadd_back(&head, ft_lstnew(str));
				free(str);
			}
	}
}
