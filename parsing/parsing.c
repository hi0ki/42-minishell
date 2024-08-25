/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:38:37 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 00:38:40 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	split_env_helper(t_lexer *tmp, char **arr, int i)
{
	t_lexer	*node;

	while (arr[i])
	{
		if (i == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(arr[0]);
		}
		else
		{
			node = lexer_lstnew(ft_strdup(arr[i]));
			node->next = tmp->next;
			node->type = WORD;
			if (tmp->next)
				tmp->next->prev = node;
			node->prev = tmp;
			tmp->next = node;
			tmp = tmp->next;
		}
		tmp->type = WORD;
		free(arr[i]);
		i++;
	}
}

static void	split_env_var(t_lexer **head)
{
	t_lexer	*tmp;
	char	**arr;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == DOLLAR && (check_variable(tmp) == 0 || 
				tmp->prev == NULL))
		{
			arr = ft_split(tmp->data, " \t");
			split_env_helper(tmp, arr, 0);
			free(arr);
		}
		tmp = tmp->next;
	}
}

static void	remove_variables(t_lexer **head)
{
	t_lexer	*tmp;

	tmp = (*head)->next;
	if ((*head)->next == NULL && 
		(*head)->type == DOLLAR && ft_strlen((*head)->data) == 0)
	{
		free((*head)->data);
		free(*head);
		(*head) = NULL;
	}
	else if ((*head)->next != NULL && 
		(*head)->type == DOLLAR && ft_strlen((*head)->data) == 0)
	{
		free((*head)->data);
		free(*head);
		(*head) = tmp;
		(*head)->prev = NULL;
	}
}

void	start_parsing(t_lexer **head, t_env *env)
{
	fill_variables(head, env);
	remove_variables(head);
	if (*head == NULL)
		return ;
	join_nodes(head);
	split_env_var(head);
	parsing_type(head);
}
