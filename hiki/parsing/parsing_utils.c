/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:38:29 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 00:38:31 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	size_node(t_lexer *head)
{
	int	i;

	i = 1;
	while (head)
	{
		if (head->type == PIPE)
			i++;
		head = head->next;
	}
	return (i);
}

int	count_cmd(t_lexer *head)
{
	int	i;

	i = 0;
	while (head && head->type != PIPE)
	{
		if (head->type >= 5 && head->type <= 8)
			head = head->next->next;
		else
		{
			i++;
			head = head->next;
		}
	}
	return (i);
}

void	num_of_files(t_list **lst, t_lexer **lexer)
{
	t_list	*tmp;
	t_lexer	*lextmp;
	int		i;

	i = 0;
	tmp = *lst;
	lextmp = *lexer;
	while (lextmp && tmp)
	{
		if (lextmp->type == PIPE)
		{
			tmp->num_of_files = i;
			i = 0;
			tmp = tmp->next;
		}
		else if (lextmp && (lextmp->type == HEREDOC || 
				lextmp->type == REDIRECT_APPEND || 
				lextmp->type == REDIRECT_INPUT || 
				lextmp->type == REDIRECT_OUTPUT))
			i++;
		if (lextmp)
			lextmp = lextmp->next;
	}
	if (lextmp == NULL && tmp != NULL)
		tmp->num_of_files = i;
}

int	check_variable(t_lexer *node)
{
	if (node && node->prev != NULL && node->prev->type != HEREDOC)
	{
		if (node->prev->prev != NULL && node->prev->prev->type != HEREDOC)
			return (0);
		else if (node->prev->prev == NULL)
			return (0);
	}
	return (1);
}

int	valid_to_split(t_lexer *node)
{
	if (node && node->prev && check_oper(node) != 0)
	{
		if (node->prev->prev && check_oper(node->prev->prev) != 0)
			return (0);
		else if (!node->prev->prev)
			return (0);
	}
	return (1);
}
