/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:48:40 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/09 12:31:39 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
	char    cwd[PATH_MAX];
	
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstrn_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}