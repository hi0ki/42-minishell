#include "minishell.h"

int get_index(char *line, char *str)
{
	int i;
	int j;

	i = 0;
	while (i <= ft_strlen(line))
	{
		j = 0;
		while (j <= ft_strlen(str))
		{
			if (str[j] == line[i])
				return (i);
			j++;
		}
		i++;
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
int check_special_char(char *str)
{
	int i;

	i = 0;
	if ((str[i] == '>' && str[i + 1] == '>') || 
		(str[i] == '<' && str[i + 1] == '<'))
		return (2);
	else if (str[i] == '<' || str[i] == '>' || 
		str[i] == '|')
		return (1);
	else if (str[i] == '\'' || str[i] == '\"')
		return (3);
	return (0);
}
