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
	while ((*node)->data[j] && (ft_isalpha((*node)->data[j]) == 1 || (*node)->data[j] == '_'))
		j++;
	if (j - i - 1 == 0)
		return ;
	var_name = ft_substr((*node)->data, i + 1, j - i - 1);
	value = get_value_env(env, var_name);
	if (value == NULL)
	{
		if ((*node)->prev != NULL && (*node)->type == DOLLAR)
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
		else
		{
			tmp = (*node)->data;
			(*node)->data = ft_substr((*node)->data,0 , i);
			j = i + ft_strlen(var_name);
			if (ft_strlen(tmp) != j)
			{
				value = ft_substr(tmp, j + 1, ft_strlen(tmp) - j);
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
	(*node)->var_quotes = -1;
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
		if (tmp->type != SQUOTE)
		{
			int i = 0;
			while (tmp->data[i])
			{
				if (tmp->data[i] == '$')
				{
					tmp->var_quotes = i;
					if (tmp->data[i + 1] == '$')
						i++;
					else
					{
						set_variable_value(&tmp, env, i);
					}
				}	
				i++;
			}
		}
		tmp = tmp->next;
	}
}
