/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:01:46 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/28 12:58:07 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	ms_status;

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
void	ft_putstrn_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

static int	is_neg(const char *s, int *i)
{
	int	sgn;

	sgn = 1;
	while ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32)
		(*i)++;
	while (s[*i] == 45 || s[*i] == 43)
	{
		if (s[*i] == 45)
			sgn = -1;
		if (s[*i + 1] == 45 || s[*i + 1] == 43)
			return (0);
		(*i)++;
	}
	return (sgn);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	somme;
	long	tmp;

	somme = 0;
	i = 0;
	sign = is_neg(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = somme;
		somme = somme * 10 + (str[i] - 48);
		if (somme / 10 != tmp && sign == -1)
			return (0);
		if (somme / 10 != tmp)
			return (-1);
		i++;
	}
	return (somme * sign);
}

int	ft_isdigit(int n)
{
	if (n >= '0' && n <= '9')
		return (1);
	else 
		return (0);
}

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void    ft_exit(char **av)
{
	ft_putstrn_fd("exit", 2);
	if (av[1] && !is_number(av[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstrn_fd(": numeric argument required", 2);
		exit(255);
	}
	else if (av[1] && av[2])
		ft_putstrn_fd("minishell: exit: too many arguments", 2);
	else
	{
		if (!av[1])
			exit(ms_status);
		else
		{
			ms_status = ft_atoi(av[1]);
			exit(ms_status % 256);
		}
	}

}

int main (int ac, char **av){
	ft_exit(av);
}