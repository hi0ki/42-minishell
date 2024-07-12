/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:16:22 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/12 11:57:10 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

typedef struct s_env{
	char			*bfr_eql;
	char			*after_eql;
	struct s_env	*next;
}	t_env;


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
void	ft_puttsrn_fd(char *s, int fd)
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
// char	*ft_strjoin(char const *s1, const char *s2)
// {
// 	char	*ptr;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) +1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		ptr[i + j] = s2[j];
// 		j++;
// 	}
// 	ptr[i + j] = '\0';
// 	return (ptr);
// }

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dst;

	i = 0;
	if (!(s1))
		return (NULL);
	while (s1[i] != '\0')
		i++;
	if (!(dst = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	add_env(char *bfr, char *aftr, t_env *env)
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
	tmp->next = new;
	new->next = NULL;
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
	add_env("OLDPWD=", cwd, env);
	retun (0);
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
		if (r != 0)
			print_error(av);
		return (r);
	}
}
