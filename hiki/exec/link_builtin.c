/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:20:00 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/21 19:21:27 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_after_built(t_list *lst, t_env *env)
{
	int r;
	int pid;

	r = 0;
	pid = fork();
	if (pid == 0)
	{
		if (lst->path_cmd != NULL)
			execve(lst->path_cmd, lst->arr, lst->envr);
		r = err_msg(lst->path_cmd, lst->arr[0]);
		exit(r);
	}
	else
	{
		waitpid(pid, &r, 0);
	}
	r = WEXITSTATUS(r);
	return (r);
}

int link_builtin(t_list *lst, t_env *env)
{
	if (ft_strcmp(lst->arr[0], "cd") == 0)
	{
		g_status = ft_cd(lst->arr, (*lst->env));
		return (1);
	}
	else if (ft_strcmp(lst->arr[0], "echo") == 0)
	{
		g_status = ft_echo(2, lst->arr, lst->out);
		return (1);
	}
	else if (ft_strcmp(lst->arr[0], "env") == 0)
	{
		g_status = ft_env((*lst->env), lst->out);
		return 1;
	}
	else if (ft_strcmp(lst->arr[0], "exit") == 0)
	{
		g_status = ft_exit(lst->arr);
		return (1);
	}
	else if (ft_strcmp(lst->arr[0], "export") == 0)
	{
		g_status = ft_export(lst->arr, lst->env, lst->out);
		return (1);
	}
	else if (ft_strcmp(lst->arr[0], "pwd") == 0)
	{
		g_status = ft_pwd(lst->out);
		return (1);
	}
	else if (ft_strcmp(lst->arr[0], "unset") == 0)
	{
		g_status = ft_unset(lst->arr, &lst);
		return (1);
	}
	return (0);
	// return(g_status);
}
