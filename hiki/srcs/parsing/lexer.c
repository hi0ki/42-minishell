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