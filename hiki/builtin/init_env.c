/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:20:49 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/22 15:35:13 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char **av)
{
	ft_putstr_fd("cd: ", 2);
	if (av[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
		ft_putstr_fd("no such file or directory: ", 2);
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
	int		i;
	t_env	*new;

	i = 0;
	while (envr[i])
	{
		new = ft_envnew(envr[i]);
		ft_envaddback(env, new);
		i++;
	}
}
