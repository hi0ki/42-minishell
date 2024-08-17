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

int err_msg(char *path, char *arr)
{
	DIR *f;
	int fd;
	// int r;

	// r = 0;
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
		ft_putstrn_fd(": permission denied", 2);
	if (path == NULL || (fd == -1 && f == NULL))
		g_status = 127;
	else
		g_status = 126;
	if (f)
		closedir(f);
	close(fd);
	return (g_status);
}


int whit_processsu(int *pid, int i)
{
	// int r;
	int j = 0;
	printf ("i = %d\n",i);
	while (j <i)
	{
		waitpid(pid[j], &g_status, 0);
		j++;
	}
	printf("******1111\n");
	return (g_status);
}
int ft_exe(t_list *lst, t_env *env)
 {
    // int r;
    int *pid;
    t_list *last;
    int fd[2];
    int fd0;
    int fd1;
    int j = 0;
    fd0 = dup(0);
    fd1 = dup(1);
    
    // r = 0;
    int size = ft_lstsize(lst);
    pid = malloc(size * sizeof(int));
    if (!pid) {
        perror("malloc error");
        return (-1);
    }

    int i = 0;
    last = ft_lstlast(lst);
    
    if (size == 1) {
        if (link_builtin(lst, env) == 1)
        {
            free(pid);
            return (g_status);
        }
    }

    while (lst)
	{
        if (i < size)
		{
            if (pipe(fd) == -1)
			{
                perror("pipe error");
                free(pid);
                return (-1);
            }
            pid[i] = fork();
            if (pid[i] < 0)
			{
                perror("fork error");
                free(pid);
                return (-1);
            }

            if (pid[i] == 0)
			{
                if (lst != last)
				{
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]);
                }
                // if (link_builtin(lst, env) == 1)
                // {
                //     free(pid);
                //     return (g_status);
                // }
                if (lst->path_cmd != NULL) \
				{
                    
                    execve(lst->path_cmd, lst->arr, lst->env);
                }
                g_status = err_msg(lst->path_cmd, lst->arr[0]);
                
                exit(g_status);
            }
			else
			{
                if (lst != last)
				{
                    dup2(fd[0], 0);
                }
                close(fd[1]);
                close(fd[0]);
            }

            i++;
        }
        lst = lst->next;
    }

    while (j < i)
	{
        waitpid(pid[j++], &g_status, 0);
        g_status = WEXITSTATUS(g_status);
    }
    dup2(fd0, 0);
    dup2(fd1, 1);

    free(pid);
    return (g_status);
}

