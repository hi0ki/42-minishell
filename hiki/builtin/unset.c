/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:46:11 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/21 15:57:57 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("chaaa1111 %d\n", i);
		if (strcmp(av[i], tmp->bfr_eql) == 0)
		{
			// printf("chaaa22222 %d\n", i);
			*env = (*env)->next;
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