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
		write(fd, str, ft_strlen(str));
		if (str != NULL)
		{
			i = 0;
			while (str[i] && str[i] != '$')
				i++;
			if (str[i] == '$')
				i++;
		}
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
