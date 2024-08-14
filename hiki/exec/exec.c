/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:08:20 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/14 16:06:06 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <unistd.h>
// #include <stdio.h>
// #include <dirent.h>
// #include <fcntl.h>

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != c)
// 	{
// 		if (s[i] == '\0')
// 			return (NULL);
// 		i++;
// 	}
// 	return ((char *)s + i);
// }

// void	ft_putstrn_fd(char *s, int fd)
// {
// 	int	i;

// 	i = 0;
// 	if (s == NULL)
// 		return ;
// 	while (s[i] != '\0')
// 	{
// 		write(fd, &s[i], 1);
// 		i++;
// 	}
// 	write(fd, "\n", 1);
// }

int err_msg(char *path, char *arr)
{
	DIR *f;
	int fd;
	int r;

	r = 0;
	fd = open(path, O_WRONLY);
	f = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arr, 2);
	if (path == NULL)
		ft_putstrn_fd(": command not found", 2);
	else if (fd == -1 && f == NULL)
		ft_putstrn_fd(": No such file or directory", 2);
	else if (fd == -1 && f != NULL)
		ft_putstrn_fd(": is a directory", 2);
	else if (fd != -1 && f == NULL)
		ft_putstrn_fd("permission denied", 2);
	if (path == NULL || (fd == -1 && f == NULL))
		r = 127;
	else
		r = 126;
	if (f)
		closedir(f);
	close(fd);
	return (r);
}

int ft_exe(t_list *lst, t_env *env)
{
	int r;
	int pid;
	int	fd[2];
	//khess tzid dik r ldakhel dial lfonction exec_after_built bach nrecuperiw lvalue dial return hna..
	r = 0;
	int sz = 3;
	int i = 00;
	int prv = -1;
	while (lst)
	{
		// khss lproto ykon haka link_builting(lst, env, &r)
		pipe(fd);
		// if (link_builtin(lst, env) == -1)
		// 	return (-1);
		pid = fork();
		if (pid == 0)
		{
			// if (i == 0)
			// 	dup2(fd[1], STDOUT_FILENO);
			// else if (i == sz - 1)
			// 	dup2(prv , STDIN_FILENO);
			// else 
			// {
			// 	dup2(fd[1], STDOUT_FILENO);
			// 	dup2(prv , STDIN_FILENO);
			// }
			// close(fd[1]);
			// close(fd[0]);
			// close (prv);
			if (lst->path_cmd != NULL)
				execve(lst->path_cmd, lst->arr, lst->env);
			r = err_msg(lst->path_cmd, lst->arr[0]);
			// perror("minishell");
			printf("mehdi\n");
			exit(r);
		}
		else
		{
			// prv = fd[0];
			waitpid(pid, &r, 0);
		}
		lst = lst->next;
	}
	// r = WEXITSTATUS(r);
	return (0);
}