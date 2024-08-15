/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:08:20 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/15 13:25:55 by mel-hime         ###   ########.fr       */
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
int whit_processsu(int *pid, int i)
{
	int r;
	int j = 0;
	printf ("i = %d\n",i);
	while (j <i)
	{
		waitpid(pid[j], &r, 0);
		j++;
	}
	printf("******1111\n");
	return (r);
}
int ft_exe(t_list *lst, t_env *env)
{
	int r;
	int *pid;
	t_list *last;
	int	fd[2];
	int fd0;
	int fd1;
	fd0=dup(0);
	fd1=dup(1);
	//khess tzid dik r ldakhel dial lfonction exec_after_built bach nrecuperiw lvalue dial return hna..
	r = 0;
	pid = malloc(ft_lstsize(lst) * sizeof(int));
	int i = 0;
	last = ft_lstlast(lst);
	if (ft_lstsize(lst) == 1)
	{
		if (link_builtin(lst, env) == 1)
			return (-1);
	}
	while (lst)
	{
		// khss lproto ykon haka link_builting(lst, env, &r)
		pid[i] = fork();
		if (pid == 0 && lst != last)
		{
			if (pipe(fd) == -1)
				return (-1);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			if (lst->path_cmd != NULL)
			{
				write(2,"erroe\n",6);
				execve(lst->path_cmd, lst->arr, lst->env);
			}	
			r = err_msg(lst->path_cmd, lst->arr[0]);
			perror("minishell");
			// printf("mehdi\n");
			exit(r);
		}
		else if (pid[i] == 0 && lst == last)
		{
			if (lst->path_cmd != NULL)
				execve(lst->path_cmd, lst->arr, lst->env);
			r = err_msg(lst->path_cmd, lst->arr[0]);
			// perror("minishell");
			// printf("mehdi\n");
			exit(127);
		}
		// else if (pid[i] > 0 && lst != last)
		// {
		// 	dup2(fd[0], 0);
		// 	// close(fd[1]);
		// }

		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		i++;
		lst = lst->next;
	}
	r = whit_processsu(pid, i);
		// printf ("*******\n");
	dup2(fd0, 0);
	dup2(fd1,1);
	r = WEXITSTATUS(r);
	return (0);
}