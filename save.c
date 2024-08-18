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
	printf("j %d\n",j);
	if (j - i > 1)
	{
		var_name = ft_substr((*node)->data, i + 1, j - i - 1);
		printf("khda smiya %s\n", var_name);
	}
	if (j - i > 1 && ft_strcmp(var_name, "?") == 0 )
	{
		printf("khda num\n");
		value = ft_itoa(g_status);
	}
	else
		value = get_value_env(env, var_name);
	if (value == NULL)
	{
		if ((j - i == ft_strlen((*node)->data) && (*node)->prev != NULL && (*node)->type == DOLLAR) || (j - i == 1 && (*node)->type == DOLLAR))
		{
			printf("lwla %d\n",j - i);
			if (j != ft_strlen((*node)->data) )
			{
				tmp = (*node)->data;
				(*node)->data = ft_substr((*node)->data, j + 1, ft_strlen((*node)->data + j));
				free(tmp);
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
				printf(">>>>>>%s<<<<<<\n", (*node)->data);
			}
		}
		else
		{
			printf("tanya\n");
			tmp = (*node)->data;
			(*node)->data = ft_substr((*node)->data,0 , i);
			j = i + ft_strlen(var_name);
			if (ft_strlen(tmp) != j)
			{
				printf("talta\n");
				value = ft_substr(tmp, j + 1, ft_strlen(tmp) - j);
				free(tmp);
				tmp = (*node)->data;
				(*node)->data = ft_strjoin((*node)->data, value);
				free(value);
			}
			free(tmp);
		}
		free(var_name);
		printf(">>>%s<<<\n", (*node)->data);
		return ;
	}
	tmp = (*node)->data;
	(*node)->data = edit_data(value, (*node)->data, i, j);;
	(*node)->len = ft_strlen((*node)->data);
	printf("3adi\n");
	printf("|>>>%s<<<|\n", (*node)->data);
	free(var_name);
	free(value);
	free(tmp);
}