/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:59:28 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/21 21:59:30 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	put_cmd_in_arr(t_list *lstmp, t_lexer *tmp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tmp->type >= 5 && tmp->type <= 8)
			tmp = tmp->next->next;
		else
		{
			lstmp->arr[i] = ft_strdup(tmp->data);
			tmp = tmp->next;
			i++;
		}
	}
	lstmp->arr[i] = NULL;
}

void	fill_arr(t_list **lst, t_lexer **head, int size)
{
	t_lexer	*tmp;
	t_list	*lstmp;

	if (!*lst)
		return ;
	lstmp = *lst;
	tmp = *head;
	while (tmp && lstmp)
	{
		if (tmp->type != PIPE)
		{
			size = count_cmd(tmp);
			lstmp->arr = malloc((size + 1) * sizeof(char *));
			if (size != 0)
				put_cmd_in_arr(lstmp, tmp, size);
			else
				lstmp->arr[0] = NULL;
			lstmp = lstmp->next;
			while (tmp && tmp->type != PIPE)
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
