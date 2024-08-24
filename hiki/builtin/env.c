/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:13:19 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/21 23:20:34 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_env *env, int fd_out)
{
	while (env)
	{
		if (env->env == 1)
		{
			ft_putstr_fd(env->bfr_eql, fd_out);
			write(fd_out, "=", 1);
			ft_putstrn_fd(env->after_eql, fd_out);
		}
		env = env->next;
	}
	return (0);
}
