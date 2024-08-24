/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:59:18 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/21 21:59:20 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_lst(t_list **lst, t_lexer **head, t_env **env, char **envr)
{
	int	size;

	*lst = NULL;
	size = size_node(*head);
	while (size > 0)
	{
		ft_lstadd_back(lst, ft_lstnew());
		size--;
	}
	num_of_files(lst, head);
	fill_files(lst, head, env);
	fill_arr(lst, head, size);
	fill_path(lst, env, envr);
}
