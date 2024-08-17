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
			return (ft_strdup(env->after_eql));
		}
		env = env->next;
	}
	return NULL;
}

void set_variable_value(t_lexer **node, t_env *env, int i)
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
		var_name = ft_substr((*node)->data, i + 1, j - i - 1);
	if (j - i > 1 && ft_strcmp(var_name, "?") == 0 )
		value = ft_itoa(g_status);
	else
		value = get_value_env(env, var_name);
	if (value == NULL)
	{
		if (((*node)->prev != NULL && (*node)->type == DOLLAR) || (j - i == 1 && (*node)->type == DOLLAR))
		{
			if (j != ft_strlen((*node)->data))
			{
				tmp = (*node)->data;
				(*node)->data = ft_substr((*node)->data, j + 1, ft_strlen((*node)->data + j));
				free(tmp);
				free(var_name);
				return ;
			}
			else
			{
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
		}
		else
		{
			tmp = (*node)->data;
			(*node)->data = ft_substr((*node)->data,0 , i);
			j = i + ft_strlen(var_name);
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
		return ;
	}
	tmp = (*node)->data;
	(*node)->data = edit_data(value, (*node)->data, i, j);;
	(*node)->len = ft_strlen((*node)->data);
	free(var_name);
	free(value);
	free(tmp);
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
			while (tmp->data[i])
			{
				if (tmp->data[i] == '$')
				{
					if (tmp->data[i + 1] == '$' || tmp->data[i + 1] == '\0')
						i++;
					else
					{
						set_variable_value(&tmp, env, i);
						i = 0;
					}
				}
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
}
