/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:38:30 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/23 15:44:56 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	go_path(int opt, t_env *env)
{
	char	*path;
	int		r;

	path = NULL;
	r = 0;
	if (opt == 0)
	{
		path = get_path(env, "HOME");
		if (!path)
		{
			r = 1;
			ft_putstrn_fd("minishell: cd: HOME not set", 2);
			return (r);
		}
		add_oldpwd(env);
	}
	r = chdir(path);
	free(path);
	path = NULL;
	if (r == -1)
		r = 1;
	return (r);
}

void	print_all_env(t_env *env, int fd_out)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(env->bfr_eql, fd_out);
		if (env->env == 1)
		{
			write(fd_out, "=\"", 2);
			ft_putstr_fd(env->after_eql, fd_out);
			write(fd_out, "\"\n", 2);
		}
		else
			write (1, "\n", 1);
		env = env->next;
	}
	return ;
}
