/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:20:00 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/06 13:20:10 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void link_builtin(t_list *lst, t_env *env)
{
	if (ft_strcmp(lst->arr[0], "cd") == 0)
		ft_cd(lst->arr, env);
	else if (ft_strcmp(lst->arr[0], "echo") == 0)
		ft_echo(2, lst->arr);
	else if (ft_strcmp(lst->arr[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(lst->arr[0], "export") == 0)
		ft_export(lst->arr, env);
	else if (ft_strcmp(lst->arr[0], "exit") == 0)
		ft_exit(lst->arr);
	else if (ft_strcmp(lst->arr[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(lst->arr[0], "unset") == 0)
		ft_unset(lst->arr, &env);
	// else
		// startexe
}