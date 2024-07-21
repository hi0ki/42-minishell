/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:13:19 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/14 18:40:16 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_env *env)
{
    // red lbal wach atbghi tb9a mpointer 3la neud lkhra wela bghiti twssel tal NULL ...hna rak drbty NULL
    while (env)
    {
		if (env->env == 1)
		{

			ft_putstr_fd(env->bfr_eql, 1);
			write(1, "=", 1);
			ft_putstrn_fd(env->after_eql, 1);
		}
			env = env->next;
    }
    return (0);
}