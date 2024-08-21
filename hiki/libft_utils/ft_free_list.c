/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:43:22 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/21 21:43:23 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_lexer(t_lexer **head)
{
	t_lexer	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->data);
		free((*head));
		*head = tmp;
	}
}

void	free_lst_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->bfr_eql);
		free((*env)->after_eql);
		free((*env));
		*env = tmp;
	}
}

void	free_list(t_list **lst)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		while (temp->arr[i] != NULL)
		{
			free(temp->arr[i]);
			i++;
		}
		free(temp->arr);
		free(temp->path_cmd);
		free(temp);
		free_files(temp->files, temp->num_of_files);
	}
}

void	free_files(t_files *file, int num_of_files)
{
	int	i;

	i = 0;
	if (file != NULL)
	{
		while (i < num_of_files)
		{
			if (file[i].file_name != NULL)
			{
				free(file[i].file_name);
				if (file[i].type == HEREDOC)
				{
					free(file[i].heredoce_name);
					close(file[i].fd);
				}
				file[i].file_name = NULL;
			}
			i++;
		}
		free(file);
		file = NULL;
	}
}
void	ft_free_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
