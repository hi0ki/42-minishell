/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:16:22 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/23 15:41:12 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_error(char **args)
{
	ft_putstr_fd("minishell: cd:", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstrn_fd(strerror(errno), 2);
	return (1);
}

static int	add_env(char *bfr, char *aftr, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->next && ft_strncmp(tmp->bfr_eql, bfr, 6))
	{
		tmp = tmp->next;
	}
	if (!ft_strncmp(tmp->bfr_eql, bfr, 6))
	{
		free(tmp->after_eql);
		tmp->after_eql = ft_strdup(aftr);
	}
	return (0);
}

int	add_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	add_env("OLDPWD", cwd, env);
	return (0);
}

char	*get_path(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->bfr_eql, key))
			return (ft_strdup(env->after_eql));
		env = env->next;
	}
	return (NULL);
}

int	ft_cd(char **av, t_env *env)
{
	int	r;

	if (!av[1])
		return (go_path(0, env));
	else 
	{
		add_oldpwd(env);
		r = chdir(av[1]);
		if (r != 0)
		{
			print_error(av);
		}
		if (r == -1)
			r = 1;
		return (r);
	}
}
