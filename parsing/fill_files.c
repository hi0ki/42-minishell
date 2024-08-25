/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:59:47 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/21 21:59:49 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	files_helper(t_list *tmp, t_lexer *lextmp, t_env **env, int i)
{
	if (lextmp->type == HEREDOC)
	{
		tmp->files[i].file_name = ft_strjoin(lextmp->next->data, "\n");
		if (lextmp->next->type == SQUOTE || lextmp->next->type == DQUOTE)
			tmp->files[i].heredoce_expand = false;
		else
			tmp->files[i].heredoce_expand = true;
		heredoce_start(&tmp->files[i], env);
	}
	else
	{
		if (lextmp->next->data[0] == '$' && ft_strlen(lextmp->next->data))
			tmp->files[i].error_file = -1;
		tmp->files[i].file_name = ft_strdup(lextmp->next->data);
	}
}

int	fill_files(t_list **lst, t_lexer **lexer, t_env **env)
{
	t_list	*tmp;
	t_lexer	*lextmp;
	int		i;

	tmp = *lst;
	lextmp = *lexer;
	tmp->files = malloc (tmp->num_of_files * sizeof(t_files));
	i = 0;
	while (lextmp && tmp)
	{
		if (lextmp->type == PIPE)
		{
			tmp = tmp->next;
			i = 0;
			tmp->files = malloc (tmp->num_of_files * sizeof(t_files));
		}
		if (lextmp->type >= 5 && lextmp->type <= 8)
		{
			tmp->files[i].type = lextmp->type;
			files_helper(tmp, lextmp, env, i);
			i++;
		}
		lextmp = lextmp->next;
	}
	return (0);
}
