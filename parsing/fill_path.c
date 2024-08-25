/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:59:55 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/21 21:59:57 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_path(char *arr, char *cmd)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(arr, "/");
	str = ft_strjoin(tmp, cmd);
	free(tmp);
	return (str);
}

static void	check_path(t_list **node, char **array, int i)
{
	char	*path;

	path = NULL;
	if (!(*node)->arr ||!(*node)->arr[0])
	{
		(*node)->path_cmd = NULL;
		return ;
	}
	while (array && array[i] && ft_strlen((*node)->arr[0]) != 0)
	{
		path = join_path(array[i], (*node)->arr[0]);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		{
			(*node)->path_cmd = ft_strdup(path);
			return (free(path));
		}
		free(path);
		path = NULL;
		i++;
	}
	if (path == NULL && access((*node)->arr[0], F_OK) == 0 && 
		access((*node)->arr[0], X_OK) == 0)
		(*node)->path_cmd = ft_strdup((*node)->arr[0]);
	else
		(*node)->path_cmd = NULL;
}

void	fill_path(t_list **lst, t_env **env, char **envr)
{
	char	**array;
	char	*str;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *lst;
	str = NULL;
	str = get_value_env(*env, "PATH");
	if (str)
		array = ft_split(str, ":");
	while (tmp)
	{
		check_path(&tmp, array, i);
		tmp->envr = envr;
		tmp->env = env;
		if (tmp)
			tmp = tmp->next;
	}
	if (str)
		return (ft_free_arr(array), free(str));
}
