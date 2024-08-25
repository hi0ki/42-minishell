/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:13:41 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/21 23:31:01 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_alpha(int c)
{
	if (c == '_')
		return (0);
	else if (c >= 'A' && c <= 'Z')
		return (0);
	else if (c >= 'a' && c <= 'z')
		return (0);
	else
		return (-1);
}

static int	is_valid_char(int c)
{
	if (c == '_')
		return (0);
	else if (c >= 'A' && c <= 'Z')
		return (0);
	else if (c >= 'a' && c <= 'z')
		return (0);
	else if (c >= '0' && c <= '9')
		return (0);
	else
		return (-1);
}

static int	is_valid_arg(char *s)
{
	int	i;

	i = 1;
	if (is_alpha(s[0]) == -1)
		return (-1);
	while (s[i] && s[i] != '=')
	{
		if (is_valid_char(s[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}

static int	env_already_exist(t_env *env, char *av)
{
	int		i;
	char	*str;

	i = 0;
	while (av[i] && av[i] != '=')
		i++;
	str = ft_substr(av, 0, i);
	while (env)
	{
		if (ft_strcmp(str, env->bfr_eql) == 0)
		{
			free(str);
			if (av[i] == '\0')
				return (0);
			if (av[i] == '=')
			{
				free(env->after_eql);
				env->after_eql = ft_substr(av, i + 1, ft_strlen(av));
				env->env = 1;
				return (0);
			}
		}
		env = env->next;
	}
	return (free(str), -1);
}

int	ft_export(char **av, t_env **env, int fd_out)
{
	int	error;
	int	i;

	i = 1;
	if (!av || !av[i])
		return (print_all_env(*env, fd_out), 0);
	while (av[i])
	{
		error = is_valid_arg(av[i]);
		if (error == -1)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(av[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			g_status = 1;
			i++;
			continue ;
		}
		if (env_already_exist(*env, av[i]) == 0)
			return (0);
		ft_envaddback(env, ft_envnew(av[i]));
		i++;
	}
	return (g_status);
}
