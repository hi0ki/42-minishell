/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:01:08 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/23 19:01:09 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*edit_heredoc_value(char *str, char *value, int i, int j)
{
	char	*tmp;
	char	*bfr;
	char	*aft;
	char	*new_str;

	bfr = ft_substr(str, 0, i - 1);
	tmp = ft_strjoin(bfr, value);
	free(bfr);
	bfr = tmp;
	aft = ft_substr(str, j, ft_strlen(str) - j);
	new_str = ft_strjoin(bfr, aft);
	free(bfr);
	free(aft);
	return (new_str);
}

static int	get_len(char *str, int i)
{
	while (str[i] && !ft_isdigit(str[i]) && str[i] != '$' && str[i] != '?' && 
		(ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	if (str[i] == '?')
		i++;
	return (i);
}

static char	*no_value(char *str, int i, int j)
{
	char	*new_str;
	char	*old_value;
	char	*value;

	if (i == 1)
	{
		if (j == i)
			new_str = ft_substr(str, j + 1, ft_strlen(str) - j);
		else
			new_str = ft_substr(str, j, ft_strlen(str) - j);
		return (new_str);
	}
	else
	{
		old_value = ft_substr(str, 0, i - 1);
		if (j - i == 0)
			value = ft_substr(str, j + 1, ft_strlen(str) - j - 1);
		else
			value = ft_substr(str, j, ft_strlen(str) - j);
		new_str = ft_strjoin(old_value, value);
		free(old_value);
		free(value);
		return (new_str);
	}
}

char	*expand_for_heredoc(char *str, int i, int j, t_env **env)
{
	char	*value;
	char	*new_str;
	char	*name;

	j = get_len(str, i);
	if (j - i == 1 && str[j - 1] == '?')
		value = ft_itoa(g_status);
	else
	{
		name = ft_substr(str, i, j - i);
		value = get_value_env(*env, name);
	}
	if (value == NULL)
	{
		if (ft_strlen(name) == ft_strlen(str) - 2)
			return (ft_strdup("\n"));
		else
			return (free(name), no_value(str, i, j));
	}
	new_str = edit_heredoc_value(str, value, i, j);
	return (new_str);
}
