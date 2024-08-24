/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 09:01:46 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/21 23:21:55 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_exit(char **av)
{
	if (av[1] && !is_number(av[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstrn_fd(": numeric argument required", 2);
		exit(255);
	}
	else if (av[1] && av[2])
	{
		ft_putstrn_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	else
	{
		if (!av[1])
			exit(g_status);
		else
		{
			g_status = ft_atoi(av[1]);
			exit(g_status % 256);
		}
	}
}
