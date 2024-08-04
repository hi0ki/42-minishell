/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:16:22 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/27 10:13:06 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	add_env(char *bfr, char *aftr, t_env *env)
{
	// should add it befor the last element (verify and check reason) " * * * ... + *"
	t_env	*new;
	t_env	*tmp;
	
	if (env && env->after_eql == NULL && env->bfr_eql == NULL)
	{
		env->bfr_eql = ft_strdup(bfr);
		env->after_eql = ft_strdup(aftr);
		return (0);
	}
	if (!(new = malloc(sizeof(t_env))))
		return(-1);
	new->bfr_eql = ft_strdup(bfr);
	new->after_eql = ft_strdup(aftr);
	tmp = env;
	while(tmp && tmp->next)
		tmp = tmp->next;
	new->next = NULL;
	tmp->next = new;
	return (0);
}

int	add_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	// char	*old_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	// if (old_pwd = ft_strjoin("OLDPWD=", cwd))
	// 	return (-1);
	// should check if it exist first then add
	add_env("OLDPWD", cwd, env);
	return (0);
}

char	*get_path(t_env *env, char *key, int n)
{
	// char	*nwd;
	while (env)
	{
		if (!ft_strncmp(env->bfr_eql, key, n))
			return (ft_strdup(env->after_eql));
		env = env->next;
	}
	return (NULL);
}

int	go_path(int opt, t_env *env)
{
	char	*path;
	int	r;

	path = NULL;
	if (opt == 0)
	{
		path = get_path(env, "HOME", 4);
		if (!path)
		{
			ft_putstr_fd("cd : HOME not set", 2);
			return (-1);
		}
		add_oldpwd(env);
	}
	else if (opt == 1)
	{
		path = get_path(env, "OLDPWD", 6);
		if (!path)
		{
			ft_putstr_fd("cd : OLDPWD not set", 2);
			return (-1);
		}
		add_oldpwd(env);
	}
	r = chdir(path);
	free(path);
	path = NULL;
	return (r);
}

int    ft_cd(char **av, t_env *env)
{
	int	r;
	
	if (!av[1])
		return (go_path(0, env));
	if (ft_strcmp(av[1], "-") == 0)
		return (go_path(1, env));
	else 
	{
		add_oldpwd(env);
		r = chdir(av[1]);
		// if (r != 0)
		// 	print_error(av);
		return (r);
	}
}
