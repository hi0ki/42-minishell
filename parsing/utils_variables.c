/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:26:28 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 18:22:24 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_name_index(t_lexer **node, int j, int i)
{
	while ((*node)->data[j] && !ft_isdigit((*node)->data[i + 1]) && 
		(*node)->data[j] != '$' && (*node)->data[j] != '?' && 
		(ft_isalnum((*node)->data[j]) == 1 || (*node)->data[j] == '_'))
		j++;
	if (j - i == 1 && (*node)->data[j] == '?')
		j++;
	return (j);
}

char	*edit_data(char *value, char *old_value, int i, int j)
{
	char	*str;
	int		len;
	int		index;

	index = 0;
	len = ft_strlen(old_value) - (j - i) + ft_strlen(value);
	str = malloc((len + 1) * sizeof(char));
	while (index < i)
	{
		str[index] = old_value[index];
		index++;
	}
	i = 0;
	while (index < len && value[i])
		str[index++] = value[i++];
	while (index < len && old_value[j])
		str[index++] = old_value[j++];
	str[index] = '\0';
	return (str);
}

char	*get_value_env(t_env *env, char *av)
{
	int		i;

	i = 0;
	if (!av)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(av, env->bfr_eql) == 0)
		{
			if (env->after_eql && env->after_eql[0])
			{
				return (ft_strdup(env->after_eql));
			}
			else
				return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

void	delete_var(t_lexer **node)
{
	t_lexer	*save;

	save = *node;
	(*node) = (*node)->prev;
	if ((*node)->next->next != NULL)
	{
		(*node)->next = (*node)->next->next;
		(*node)->next->prev = (*node);
	}
	else
		(*node)->next = NULL;
	free(save->data);
	free(save);
}
