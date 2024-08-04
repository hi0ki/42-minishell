/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:46:11 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/28 09:01:43 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// typedef struct s_env{
// 	char			*bfr_eql;
// 	char			*after_eql;
// 	int				env;
// 	struct s_env	*next;
// }	t_env;

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_substr(char *s, int start, int len)
// {
// 	int	i;
// 	char	*str;

// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen(s) <= start)
// 		len = 0;
// 	else if (ft_strlen(s) <= (start + len))
// 		len = (ft_strlen(s) - start);
// 	str = malloc(len * (sizeof(char)) + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = s[i + start];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

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


void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return ;
}

void	free_node(t_env *env)
{
	ft_free(env->bfr_eql);
	ft_free(env->after_eql);
	ft_free(env);
	return ;
}

int ft_unset(char **av, t_env **env)
{
	t_env   *tmp;
	t_env   *todel;
	int     i;

	tmp = *env;
	i = 1;
	if (!av[1])
		return (0);
	if (!env || !(*env))
		return (0);
	while (av[i])
	{
		// printf("chaaa1111 %d\n", i);
		if (strcmp(av[i], tmp->bfr_eql) == 0)
		{
			// printf("chaaa22222 %d\n", i);
			(*env) = (*env)->next;
			free_node(tmp);
			// printf("chaaa3333 %d\n", i);
			i = 0;
		}
		i++;
	}
	i = 1;
	while (av[i])
	{
		tmp = (*env);
		while (tmp && tmp->next)
		{
			if (strcmp(av[i], tmp->next->bfr_eql) == 0)
			{
				todel = tmp->next;
				tmp->next = tmp->next->next;
				free_node(todel);
				// printf("chaaa3333 %d\n", i);
				break ;
			}
			tmp = tmp->next;
		}
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
// // 	// sleep (1);
// // 	// if (!env)
// // 	// 	printf("l9wada hadi\n");
	
// 	// ft_export(av, env);
// 	ft_unset(av, &env);

// 	while (env)
// 	{
// 		printf("befor '=' : %s\n", env->bfr_eql);
// 		printf("------------------------------------------------------------------------\n");
// 		printf("after '=' : %s\n", env->after_eql);
// 		printf("------------------------------------------------------------------------\n");
// 		env = env->next;
// 	}

// // 	// char ss[200];
// // 	// getcwd(ss, 200);
// // 	// printf("befor => %s\n", ss);
// // 	// // chdir("/Users/mel-hime");
// // 	// ft_cd(av, env);
// // 	// getcwd(ss, 200);
// // 	// printf("after => %s\n", ss);
// // 	// // sleep (1);

// 	return (0);
// }