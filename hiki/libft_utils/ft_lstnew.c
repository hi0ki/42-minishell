/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:25:54 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 22:33:32 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lstnew(void)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->out = 1;
	node->in = 0;
	node->pipe_fd[0] = 0;
	node->pipe_fd[1] = 1;
	node->prev_in = 0;
	node->next = NULL;
	node->path_cmd = NULL;
	node->arr = NULL;
	node->files = NULL;
	node->error = true;
	return (node);
}

t_lexer	*lexer_lstnew(char *data)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->data = data;
	node->type = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
