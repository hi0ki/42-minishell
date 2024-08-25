/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:59:16 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/20 23:59:18 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	write_error(t_lexer *tmp)
{
	if (tmp->error_quotes == -1)
	{
		ft_putstrn_fd("minishell: unexpected EOF while looking for matching", 
			2);
		g_status = 258;
		return (-1);
	}
	else if (tmp->type == PIPE && (tmp->prev == NULL || tmp->next == NULL || 
			(tmp->next != NULL && tmp->next->type == PIPE)))
	{
		ft_putstrn_fd("minishell: syntax error pipe", 2);
		g_status = 258;
		return (-1);
	}
	else if (check_oper(tmp) == 0 && (tmp->next == NULL || 
			check_oper(tmp->next) == 0 || (tmp->next->type == SPC && 
				(tmp->next->next == NULL || tmp->next->next->type == PIPE || 
					check_oper(tmp->next->next) == 0))))
	{
		ft_putstrn_fd("minishell: syntax error files", 2);
		g_status = 258;
		return (-1);
	}
	return (0);
}

int	error_handler(t_lexer *lexer)
{
	int		status;
	t_lexer	*tmp;

	status = 0;
	tmp = lexer;
	while (tmp)
	{
		if (write_error(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
