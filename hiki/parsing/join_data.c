/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:37:55 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 00:37:57 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void join_nodes(t_lexer **head)
{
	t_lexer *tmp;
	t_lexer *save;
	char	*s_data;

	tmp = *head;
	while (tmp)
	{
		if (tmp != NULL && check_oper(tmp) != 0
			&& tmp->prev != NULL && check_oper(tmp->prev) != 0)
		{
			if (tmp->prev != NULL && tmp->prev->type != PIPE && tmp->type != PIPE && ft_strcmp(tmp->data, " ") != 0 && ft_strcmp(tmp->data, "\t") != 0 &&
				ft_strcmp(tmp->prev->data, " ") != 0 && ft_strcmp(tmp->prev->data, "\t") != 0 )
			{
				tmp = tmp->prev;
				s_data = tmp->data;
				tmp->data = ft_strjoin(tmp->data, tmp->next->data);
				// tmp->type = WORD;
				save = tmp->next;
				if (tmp->next->next != NULL)
				{
					tmp->next->next->prev = tmp;
					tmp->next = tmp->next->next;
				}
				else
					tmp->next = NULL;
				free(s_data);
				free(save->data);
				free(save);
			}
		}
		tmp = tmp->next;
	}
}
