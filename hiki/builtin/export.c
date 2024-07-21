/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:13:41 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/21 12:07:56 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_env{
// 	char			*bfr_eql;
// 	char			*after_eql;
// 	int				env;
// 	struct s_env	*next;
// }	t_env;

// int	ft_strlen(char *s)
// {
// 	int i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while(s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(char *s1)
// {
// 	int		i;
// 	char	*dst;

// 	i = 0;
// 	if (!(s1))
// 		return (NULL);
// 	while (s1[i] != '\0')
// 		i++;
// 	if (!(dst = malloc(sizeof(char) * (i + 1))))
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		dst[i] = s1[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }
// void	ft_putstr_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}
// }
// void	ft_putstrn_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (s == NULL)
// 		return ;
// 	while (s[i] != '\0')
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}
// 	write(fd, "\n", 1);
// }

void    print_all_env(t_env *env)
{
	int i;

	i = 0;
	if (!env)
		return ;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->bfr_eql, 1);
		if (env->env == 1)
		{
			write(1, "=", 1);
			ft_putstrn_fd(env->after_eql, 1);        
		}
		else
			write (1, "\n", 1);
		env = env->next;
	}
	return ;
}

int	is_alpha(int c)
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

int	is_valid_char(int c)
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

int	is_valid_arg(char *s)
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

// char	*ft_substr(char *s, unsigned int start, int len)
// {
// 	char	*sbstr;
// 	int		i;
// 	int		flen;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s) || !len)
// 		return (ft_strdup(""));
// 	flen = ft_strlen(s + start);
// 	if (flen > len)
// 		flen = len;
// 	sbstr = (char *)malloc(flen + 1);
// 	if (!sbstr)
// 		return (NULL);
// 	while (i < flen)
// 	{
// 		sbstr[i] = s[i + start];
// 		i++;
// 	}
// 	sbstr[i] = '\0';
// 	return (sbstr);
// }
// int	ft_strncmp(char *s1, char *s2,int n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[i] == s2[i])
// 	{
// 		if ((s1[i] == '\0' && s2[i] == '\0') || i == n - 1)
// 			return (0);
// 		i++;
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

int	env_already_exist(t_env *env, char *av)
{
	int		i;

	i = 0;
	while (av[i] && av[i] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(av, env->bfr_eql, i) == 0)
		{
			if (av[i] == '\0')
				return (0);
			if (av[i] == '=')
			{
				free(env->after_eql);
				// env->after_eql = NULL;
				env->after_eql = ft_substr(av, i + 1, ft_strlen(av));
				env->env = 1;
				return (0);
			}
		}
		env = env->next;
	}
	return (-1);
}

// t_env	*ft_envnew(char *s)
// {
// 	t_env	*n1;
// 	int		i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	n1 = malloc(sizeof(t_env));
// 	if (!n1)
// 		return (NULL);
// 	n1->env = 0;
// 	while (s[i] && s[i] != '=')
// 		i++;
// 	n1->bfr_eql = ft_substr(s, 0, i);
// 	if (s[i] && s[i] == '=')
// 		n1->env = 1;
// 	n1->after_eql = ft_substr(s, i + 1, ft_strlen(s));
// 	n1->next = NULL;
// 	return (n1);
// }

// void	ft_envaddback(t_env **head, t_env *new)
// {
// 	t_env	*tmp;

// 	tmp = *head;
// 	if (!(*head))
// 	{
// 		// printf("rah dkhlt \n");
// 		*head = new;
// 		return ;
// 	}

// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

int	ft_export(char **av, t_env *env)
{
	int error;
	int i;

	i = 1;
	if (!av || !av[i])
	{
		print_all_env(env);
		return (0);
	}
	while (av[i])
	{
		error = is_valid_arg(av[i]);
		if (error == -1)
		{
			printf("minishell: export: '%s': not a valid identifier\n", av[i]);
			return (-1);
		}
		if (env_already_exist(env, av[i]) == 0)
			return (0);
		ft_envaddback(&env, ft_envnew(av[i]));
		i++;
	}
	return (0);
}

// int main (int ac, char **av, char **envr)
// {
// 	(void)ac;
// // 	// (void)av;
// 	t_env	*env;
// 	t_env	*new;
// 	int i = 0;

// 	env = NULL;
// 	while (envr[i])
// 	{
// 		// printf("%s\n", envr[i]);
// 		new = ft_envnew(envr[i]);
// 		// printf("i'm %d\n", i);
// 		ft_envaddback(&env, new);
// 		// break;
// 		i++;
// 	}
// 	// sleep (1);
// 	// if (!env)
// 	// 	printf("l9wada hadi\n");
	
	// ft_export(av, env);

// 	while (env)
// 	{
// 		printf("befor '=' : %s\n", env->bfr_eql);
// 		printf("------------------------------------------------------------------------\n");
// 		printf("after '=' : %s\n", env->after_eql);
// 		printf("------------------------------------------------------------------------\n");
// 		env = env->next;
// 	}

// 	// char ss[200];
// 	// getcwd(ss, 200);
// 	// printf("befor => %s\n", ss);
// 	// // chdir("/Users/mel-hime");
// 	// ft_cd(av, env);
// 	// getcwd(ss, 200);
// 	// printf("after => %s\n", ss);
// 	// // sleep (1);

// 	return (0);
// }