#include "minishell.h"

char *ft_str_alloc(char *line, int size)
{
	char *str;
	int	i;

	i = 0;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
