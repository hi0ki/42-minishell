/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:51:16 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/19 11:51:35 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

int	ft_strncmp(char *s1, char *s2,int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if ((s1[i] == '\0' && s2[i] == '\0') || i == n - 1)
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_echo(int ac, char **av)
{
	int	i = 1;
	int j = 1;
	int	option = 0;

	if (ac > 1)
	{
		while (av[i] && !ft_strncmp(av[i], "-n", 2))
		{
			while (av[i][j] && av[i][j] == 'n')
				j++;
			if (av[i][j] == '\0')
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

// int main (int ac, char **av)
// {
// 	ft_echo(ac, av);
// }

//ba9i lia '-nnnn'