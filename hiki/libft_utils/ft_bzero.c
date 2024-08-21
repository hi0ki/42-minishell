/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:48:27 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/21 16:27:16 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(char *str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

char	**env_to_tab(t_env *env)
{
	t_env	*tmp;
	char 	**str;
	int i;

	i = 0;
	tmp = env;
	str = malloc(ft_envsize(env) * sizeof(char *));
	while (tmp)
	{
		str[i] = ft_strjoin(ft_strjoin(tmp->bfr_eql, "="), tmp->after_eql);
		i++;
		tmp = tmp->next;
	}
	return (str);
}
