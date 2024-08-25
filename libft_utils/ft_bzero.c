/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:48:27 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/23 13:40:16 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	*bfr;
	char	**str;
	int		i;

	i = 0;
	tmp = env;
	str = malloc((ft_envsize(env) + 1) * sizeof(char *));
	while (tmp)
	{
		bfr = ft_strjoin(tmp->bfr_eql, "=");
		str[i] = ft_strjoin(bfr, tmp->after_eql);
		free(bfr);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}

void	ft_close_pr(t_list *lst)
{
	if (lst->prev_in != 0)
		close (lst->prev_in);
	if (lst->next)
		close (lst->pipe_fd[1]);
	return ;
}
