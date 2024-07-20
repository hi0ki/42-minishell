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

#include "minishell.h"

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
			else
			{
				ft_putstr(av[i]);
				write(1, " ", 1);
			}
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

// ba9i lia '-nnnn'