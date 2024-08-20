#include "minishell.h"

char *edit_data(char *value, char *old_value, int i, int j)
{
	char *str;
	int		len;
	int index;

	index = 0;
	len = ft_strlen(old_value) - (j - i) + ft_strlen(value);
	str = malloc((len + 1) * sizeof(char));
	while(index < i)
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
	return str;
}
char *get_value_env(t_env *env, char *av)
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
	return NULL;
}
static void delete_var(t_lexer **node)
{
	t_lexer *save;

	save = *node;
	(*node) = (*node)->prev;
	if ((*node)->next->next != NULL)
	{
		(*node)->next = (*node)->next->next;
	}
	else
	{
		(*node)->next = NULL;
	}
	free(save->data);
	free(save);
}

int set_variable_value(t_lexer **node, t_env *env, int i)
{
	char	*var_name;
	char	*value;
	char	*tmp;
	t_lexer *save;
	int		j;

	j = i;
	j++;
	var_name = NULL;
	while ((*node)->data[j] && !ft_isdigit((*node)->data[i + 1]) && (*node)->data[j] != '$' && (*node)->data[j] != '?' &&
		(ft_isalnum((*node)->data[j]) == 1 || (*node)->data[j] == '_'))
		j++;
	if ((*node)->data[j] == '?')
		j++;
	if (j - i > 1)
	{
		var_name = ft_substr((*node)->data, i + 1, j - i - 1);
	}
	if (j - i > 1 && ft_strcmp(var_name, "?") == 0 )
	{
		value = ft_itoa(g_status);
	}
	else
	{
		value = get_value_env(env, var_name);
	}
	if (value == NULL)
	{
		if (value == NULL && (*node)->type == DOLLAR && j == ft_strlen((*node)->data) && 
			((*node)->prev && (!check_oper((*node)->prev) || ((*node)->prev->prev && !check_oper((*node)->prev->prev)))))
		{
			return (i + 1);
		}
		if (j - i == 1)
		{
			if (j - i == 1)
			{
				tmp = (*node)->data;
				(*node)->data = ft_substr((*node)->data, 0 , i);
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
		else
		{
			tmp = (*node)->data;
			(*node)->data = ft_substr((*node)->data,0 , i);
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
		}
		free(var_name);
		if (ft_strlen((*node)->data) == 0 && (*node)->prev != NULL)
			delete_var(node);
		return (i);
	}
	tmp = (*node)->data;
	(*node)->data = edit_data(value, (*node)->data, i, j);;
	i = i + ft_strlen(value);
	free(var_name);
	free(value);
	free(tmp);
	return (i);
}
void fill_variables(t_lexer **head, t_env *env)
{
	t_lexer *tmp;

	tmp = *head;
	while (tmp)
	{  
		if (tmp->type != SQUOTE && (check_variable(tmp) == 0 || tmp->prev == NULL))
		{
			int i = 0;
			while (tmp && tmp->data[i])
			{
				if (tmp->data[i] == '$' && tmp->data[i + 1] != '\0')
				{
					if (tmp->data[i + 1] == '$')
					{
						i+=2;
					}
					else
					{
						i = set_variable_value(&tmp, env, i);
					}
				}
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
}
//export a="x"$
// echo $a$
// export a=$
// echo $a$