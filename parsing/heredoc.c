/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 00:37:49 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/23 15:40:43 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	sig_heredoc(int sig)
{
	(void) sig;
	g_status = 1;
	write(1, "\n", 1);
	exit (g_status);
}

static char	*start_expand(char *str, int i, t_env **env)
{
	while (str[i])
	{
		if (str[i] == '$' && str[i + 2])
		{
			if (str[i + 1] == '$')
				i += 2;
			else
			{
				str = expand_for_heredoc(str, i + 1, 0, env);
				i = 0;
			}
		}
		else
			i++;
	}
	return (str);
}

static void	heredoce_handler(t_files *file, t_env **env, int fd)
{
	char	*str;
	int		i;

	signal(SIGINT, SIG_DFL);
	signal(SIGINT, sig_heredoc);
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str || ft_strcmp(str, file->file_name) == 0)
			break ;
		if (str != NULL && file->heredoce_expand != false)
		{
			i = 0;
			str = start_expand(str, i, env);
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
}

void	heredoce_start(t_files *file, t_env **env)
{
	int		fd;
	char	*name;
	int		pid;

	name = generate_heredoc_name();
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file->fd == -1)
		perror(file->file_name);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_heredoc);
		heredoce_handler(file, env, fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		close(fd);
	}
	file->heredoce_name = ft_strdup(name);
	free(name);
}
