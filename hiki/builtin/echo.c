/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:51:16 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/21 11:11:40 by mel-hime         ###   ########.fr       */
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

int	ft_echo(int ac, char **av, int fd_out)
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
				ft_putstr_fd(av[i], fd_out);
				write(fd_out, " ", 1);
			}
			i++;
		}
		while (av[i])
		{
			ft_putstr_fd(av[i], fd_out);
			if (av[i + 1])
				write(fd_out, " ", 1);
			i++;
		}

	}
	if (option == 0)
		write (fd_out, "\n", 1);
	return (0);
}
