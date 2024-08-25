/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:51:16 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/22 16:17:07 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_echo_nor(char **av, int fd_out, int *i, int *o)
{
	int	j;

	j = 1;
	while (av[(*i)] && !ft_strncmp(av[(*i)], "-n", 2))
	{
		j = 1;
		while (av[(*i)][j] && av[(*i)][j] == 'n')
			j++;
		if (av[(*i)][j] == '\0')
			*o = 1;
		else
		{
			ft_putstr_fd(av[(*i)], fd_out);
			write(fd_out, " ", 1);
		}
		(*i)++;
	}
	while (av[*i])
	{
		ft_putstr_fd(av[(*i)], fd_out);
		if (av[(*i) + 1])
			write(fd_out, " ", 1);
		(*i)++;
	}
}

int	ft_echo(int ac, char **av, int fd_out)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (ac > 1)
		ft_echo_nor(av, fd_out, &i, &option);
	if (option == 0)
		write (fd_out, "\n", 1);
	return (0);
}
