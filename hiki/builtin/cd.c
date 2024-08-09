/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:16:22 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/09 12:01:10 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		print_error(char **args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstrn_fd(strerror(errno), 2);
	return (1);
}

int	add_env(char *bfr, char *aftr, t_env *env)
{
	t_env	*tmp;
	// if (env && env->after_eql == NULL && env->bfr_eql == NULL)
	// {
	// 	env->bfr_eql = ft_strdup(bfr);
	// 	env->after_eql = ft_strdup(aftr);
	// 	return (0);
	// }
	// if (!(new = malloc(sizeof(t_env))))
	// 	return(-1);
	// new->bfr_eql = ft_strdup(bfr);
	// new->after_eql = ft_strdup(aftr);
	tmp = env;
	while(tmp && tmp->next && ft_strncmp(tmp->bfr_eql, bfr, 6))
	{
		tmp = tmp->next;
		// printf("%d\n", i);
		// printf("---------------\n");
	}
	// printf("%s-- %d\n", tmp->bfr_eql, ft_strlen(tmp->bfr_eql));
	// new->next = NULL;
	// tmp->next = new;
	if (!ft_strncmp(tmp->bfr_eql, bfr, 6))
	{
		// printf("\n\nHAAAAAAAA\n\n");
		free(tmp->after_eql);
		tmp->after_eql = ft_strdup(aftr);
	}
	return (0);
}

int	add_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	// if (old_pwd == ft_strjoin("OLDPWD=", cwd))
	// 	return (-1);
	// should check if it exist first then add
	add_env("OLDPWD", cwd, env);
	return (0);
}

char	*get_path(t_env *env, char *key)
{
	// char	*nwd;
	while (env)
	{
		if (!ft_strcmp(env->bfr_eql, key))
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
		path = get_path(env, "HOME");
		if (!path)
		{
			ft_putstrn_fd("minishell: cd: HOME not set", 2);
			return (r);
		}
		add_oldpwd(env);
	}
	r = chdir(path);
	free(path);
	path = NULL;
	if (r == -1)
		r = 1;
	return (r);
}

int    ft_cd(char **av, t_env *env)
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
