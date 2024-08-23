/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:46:11 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/23 15:41:21 by mel-hime         ###   ########.fr       */
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
	env->bfr_eql = NULL;
	ft_free(env->after_eql);
	env->after_eql = NULL;
	ft_free(env);
	env = NULL;
	return ;
}

void	unset_mid(char **av, t_list **lst)
{
	int		i;
	t_env	*tmp;
	t_env	*todel;

	i = 1;
	while (av[i])
	{
		tmp = (*(*lst)->env);
		while (tmp && tmp->next)
		{
			if (strcmp(av[i], tmp->next->bfr_eql) == 0)
			{
				todel = tmp->next;
				tmp->next = tmp->next->next;
				free_node(todel);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return ;
}

int	ft_unset(char **av, t_list **lst)
{
    t_env	*tmp, *prev;
    int		i;

    i = 1;
    if (!av[1])
        return (0);
    if (!(*lst)->env || !(*(*lst)->env))
        return (0);
    tmp = (*(*lst)->env); // Initialize tmp here
    prev = NULL;
    while (av[i])
    {
        if (strcmp(av[i], tmp->bfr_eql) == 0)
        {
            t_env *nextNode = tmp->next; // Save the next node before freeing tmp
            if (ft_envsize(tmp) == 1)
                return (free(tmp->after_eql), free(tmp->bfr_eql), 0);
            if (prev == NULL) // This is the first node
                (*(*lst)->env) = nextNode;
            else
                prev->next = nextNode;
            free_node(tmp);
            tmp = nextNode; // Set tmp to the next node
            i = 0;
        }
        else
        {
            prev = tmp;
            tmp = tmp->next;
        }
        i++;
    }
    unset_mid(av, lst);
    return (0);
}
