/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:32:48 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 00:32:51 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_one_char(t_lexer **node, int i, int j)
{
	char	*tmp;
	char	*value;

	if (j - i == 1)
	{
		tmp = (*node)->data;
		(*node)->data = ft_substr((*node)->data, 0, i);
		if (ft_strlen(tmp) != i)
		{
			value = ft_substr(tmp, j + 1, ft_strlen(tmp) - j);
			free(tmp);
			tmp = (*node)->data;
			(*node)->data = ft_strjoin((*node)->data, value);
			free(value);
		}
		free(tmp);
	}
}

static int	handle_no_variable(t_lexer **node, char *var_name, int i, int j)
{
	char	*tmp;
	char	*value;

	tmp = (*node)->data;
	(*node)->data = ft_substr((*node)->data, 0, i);
	j = i + ft_strlen(var_name);
	i = ft_strlen((*node)->data);
	if (ft_strlen(tmp) != j)
	{
		value = ft_substr(tmp, j + 1, ft_strlen(tmp) - j);
		free(tmp);
		tmp = (*node)->data;
		(*node)->data = ft_strjoin((*node)->data, value);
		free(value);
	}
	free(tmp);
	return (i);
}

static int	handle_no_value(t_lexer **node, char *var_name, int i, int j)
{
	if ((*node)->type == DOLLAR && j == ft_strlen((*node)->data) && 
		((*node)->prev && (!check_oper((*node)->prev) || 
				((*node)->prev->prev && !check_oper((*node)->prev->prev)))))
		return (free(var_name), i + 1);
	if (j - i == 1)
		handle_one_char(node, i, j);
	else
		i = handle_no_variable(node, var_name, i, j);
	free(var_name);
	if (ft_strlen((*node)->data) == 0 && (*node)->prev != NULL)
		delete_var(node);
	return (i);
}

int	set_variable_value(t_lexer **node, t_env *env, int i)
{
	char	*var_name;
	char	*value;
	char	*tmp;
	int		j;

	j = i;
	j++;
	var_name = NULL;
	j = get_name_index(node, j, i);
	if (j - i > 1)
		var_name = ft_substr((*node)->data, i + 1, j - i - 1);
	if (j - i > 1 && ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(g_status);
	else
		value = get_value_env(env, var_name);
	if (value == NULL)
		return (handle_no_value(node, var_name, i, j));
	tmp = (*node)->data;
	(*node)->data = edit_data(value, (*node)->data, i, j);
	i = i + ft_strlen(value);
	free(tmp);
	free(value);
	free(var_name);
	return (i);
}

void	fill_variables(t_lexer **head, t_env *env)
{
	t_lexer	*tmp;
	int		i;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type != SQUOTE && (check_variable(tmp) == 0 || 
				tmp->prev == NULL))
		{
			i = 0;
			while (tmp && tmp->data[i])
			{
				if (tmp->data[i] == '$' && tmp->data[i + 1] != '\0')
				{
					if (tmp->data[i + 1] == '$')
						i += 2;
					else
						i = set_variable_value(&tmp, env, i);
				}
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
}
