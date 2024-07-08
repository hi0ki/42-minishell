/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:51:16 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/08 10:04:53 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_echo(int ac, char **av)
{
	int	i = 1;
	int	option = 0;

	if (ac > 1)
	{
		while (av[i] && !ft_strcmp(av[i], "-n"))
		{
			option = 1;
			i++;
		}
		while (av[i])
		{
			ft_putstr(av[i]);
			if (av[i + 1])
				write(1, " ", 1);
			i++;
		}

	}
	if (option == 0)
		write (1, "\n", 1);
}

int main (int ac, char **av)
{
	ft_echo(ac, av);
}