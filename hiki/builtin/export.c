/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:13:41 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/09 12:30:06 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			write(1, "=\"", 2);
			ft_putstr_fd(env->after_eql, 1);
			write(1, "\"\n", 2);     
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


int	env_already_exist(t_env *env, char *av)
{
	int		i;
	char *str;

	i = 0;
	while (av[i] && av[i] != '=')
		i++;
	str = ft_substr(av, 0, i);
	while (env)
	{
		// printf("%s|%s \n", str, env->bfr_eql);
		if (ft_strcmp(str, env->bfr_eql) == 0)
		{
			free(str);
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
	free(str);
	return (-1);
}

// int	manag_dlr_len(char *str)
// {
// 	int	i = 0;
// 	int	j = 0;

// 	if (!str)
// 		return (0);
// 	while(str[i])
// 	{
// 		// printf("%c\n", str[i]);
// 		if(str[i] == '$')
// 			j++;
// 		i++;
// 		j++;
// 		// printf("%d\n", i);
// 		// printf("%d\n", j);
// 		// printf("----\n");
// 	}
// 	return (j);
// }

// char *manag_dlr(char *str)
// {
// 	char	*s;
// 	int		i = 0;
// 	int		j = 0;

// 	if (!str)
// 		return (NULL);
// 	s = malloc(manag_dlr_len(str));
// 	if (!s)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			s[j++] = '\\';
// 		s[j] = str[i];
// 		j++;
// 		i++;
// 	}
// 	s[j] = '\0';
// 	return (s);
// }

int	ft_export(char **av, t_env *env)
{
	int error;
	int i;
	// char *str_dlr;

	i = 1;
	if (!av || !av[i])
		return (print_all_env(env), 0);
	while (av[i])
	{
		error = is_valid_arg(av[i]);
		if (error == -1)
		{
			printf("minishell: export: '%s': not a valid identifier\n", av[i]);
			i++;
			continue ;
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