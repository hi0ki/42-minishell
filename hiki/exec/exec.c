/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:08:20 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/03 19:13:39 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
void	ft_putstrn_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int err_msg(char *path)
{
	DIR *f;
	int fd;
	int r;

	fd = open(path, O_WRONLY);
	f = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (!ft_strchr(path, '/'))
		ft_putstrn_fd(": command not found", 2);
	else if (fd == -1 && f == NULL)
		ft_putstrn_fd(": No such file or directory", 2);
	else if (fd == -1 && f != NULL)
		ft_putstrn_fd(": is a directory", 2);
	else if (fd != -1 && f == NULL);
		ft_putstrn_fd("permission denied", 2);
	//'''''''''''''''''''''''''
}

int ft_exec(char *path, char **av, char **env)
{
	int r;
	int id;

	r = 0;
	id = fork();
	if (id = 0)
	{
		execve(path, av, env);
		exit(r);
	}
	
}