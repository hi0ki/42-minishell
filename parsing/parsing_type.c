/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:38:18 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 00:38:24 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remove_spaces(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*save;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == SPC)
		{
			save = tmp;
			tmp = tmp->prev;
			if (tmp->next->next != NULL)
			{
				tmp->next = tmp->next->next;
				tmp->next->prev = tmp;
			}
			else
				tmp->next = NULL;
			free(save->data);
			free(save);
			save = NULL;
		}
		tmp = tmp->next;
	}
}

static void	remove_front_space(t_lexer **head)
{
	t_lexer	*tmp;

	if ((*head)->type == SPC)
	{
		tmp = *head;
		*head = (*head)->next;
		if (*head)
			(*head)->prev = NULL;
		free(tmp->data);
		free(tmp);
	}
}

static void	give_type(t_lexer **node)
{
	if (check_variable(*node) == 1)
		return ;
	if ((*node)->type >= 5 && (*node)->type <= 8)
		return ;
	else if ((*node)->prev == NULL || ft_strcmp((*node)->prev->data, "|") == 0)
		(*node)->type = CMD;
	else if (ft_strcmp((*node)->data, "|") == 0 && (*node)->type == PIPE)
		(*node)->type = PIPE;
	else
		(*node)->type = ARG;
}

void	parsing_type(t_lexer **head)
{
	t_lexer	*tmp;

	remove_front_space(head);
	remove_spaces(head);
	tmp = *head;
	while (tmp)
	{
		give_type(&tmp);
		tmp = tmp->next;
	}
}
