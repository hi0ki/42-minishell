/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ansa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:37:49 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/22 00:37:52 by eel-ansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_heredoc_name(void)
{
	static int	i;
	char		*num;
	char		*name;

	i++;
	num = ft_itoa(i);
	name = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (name);
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

static char *edit_heredoc_value(char *str, char *value, int i, int j)
{
	char *tmp;
	char *bfr;
	char *aft;
	char *new_str;

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

char    *expand_for_heredoc(char *str, int i, int j, t_env **env)
{
	char	*value;
	char	*old_value;
	char	*new_str;
	char	*name;
	int		len;

	j = get_len(str, i);
	if (j - i == 1 && str[j - 1] == '?')
	{
		value = ft_itoa(g_status);
	}
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
		{
			if (i == 1)
			{
				if (j == i)
					new_str = ft_substr(str, j + 1, ft_strlen(str) - j);
				else
					new_str = ft_substr(str, j, ft_strlen(str) - j);
				free(name);
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
				free(name);
				free(old_value);
				free(value);
				return (new_str);
			}
		}
	}
	new_str = edit_heredoc_value(str, value, i, j);
    return (new_str);
}

static void	heredoce_handler(t_files *file, t_env **env, int fd)
{
	char	*str;
	int		i;

	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(1);
		if (!str || ft_strcmp(str, file->file_name) == 0)
			break ;
		if (str != NULL)
		{
			i = 0;
			while (str[i])
			{
				if (str[i] == '$' && str[i + 1] != '$' && str[i + 1])
				{
					str = expand_for_heredoc(str, i + 1, 0, env);
					i = 0;
				}
				i++;
			}
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
}


void	heredoce_start(t_files *file, t_env **env)
{
	char	*str;
	int		fd;
	char	*name;
	int		pid;

	name = generate_heredoc_name();
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file->fd == -1)
	{
		printf("exit f heredoc\n");
		perror(file->file_name);
		exit(g_status);
	}
	pid = fork();
	if (pid == 0)
	{
		heredoce_handler(file, env, fd);
		close(fd);
		exit(0);
	}
	else
		waitpid(pid, &g_status, 0);
	file->heredoce_name = ft_strdup(name);
	free(name);
}
