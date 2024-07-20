/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:16:22 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/19 19:50:57 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char **av)
{
	ft_putstr_fd("cd: ", 2);
	if (av[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		//try that function the retreve the message error exactly
		ft_putstr_fd("no such file or directory: ", 2);
		// ft_putstr_fd(": ", 2);
	}
	ft_putstrn_fd(av[1], 2);
}
t_env	*ft_envnew(char *s)
{
	t_env	*n1;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	n1 = malloc(sizeof(t_env));
	if (!n1)
		return (NULL);
	n1->env = 0;
	while (s[i] && s[i] != '=')
		i++;
	n1->bfr_eql = ft_substr(s, 0, i);
	if (s[i] && s[i] == '=')
		n1->env = 1;
	n1->after_eql = ft_substr(s, i + 1, ft_strlen(s));
	n1->next = NULL;
	return (n1);
}

void	ft_envaddback(t_env **head, t_env *new)
{
	t_env	*tmp;

	tmp = *head;
	if (!(*head))
	{
		*head = new;
		return ;
	}

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	env_init(t_env **env, char **envr)
{
	int i = 0;
	t_env *new;

	while (envr[i])
	{
		new = ft_envnew(envr[i]);
		ft_envaddback(env, new);
		i++;
	}
}

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
	char	*old_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (-1);
	// if (old_pwd = ft_strjoin("OLDPWD=", cwd))
	// 	return (-1);
	// should check if it exist first then add
	add_env("OLDPWD", cwd, env);
	return (0);
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

char	*get_path(t_env *env, char *key, int n)
{
	char	*nwd;
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
	// free(path);
	// path = NULL;
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
