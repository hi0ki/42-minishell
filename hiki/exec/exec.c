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
int ft_exe(t_list *lst, t_env *env) {
    int r;
    int *pid;
    t_list *last;
    int fd[2];
    int fd0;
    int fd1;
    fd0 = dup(0);
    fd1 = dup(1);
    
    r = 0;
    int size = ft_lstsize(lst);
    pid = malloc(size * sizeof(int));
    if (!pid) {
        perror("malloc error");
        return (-1);
    }

    int i = 0;
    last = ft_lstlast(lst);
    
    if (size == 1) {
        if (link_builtin(lst, env) == 1) {
            free(pid); // Libérer la mémoire en cas d'erreur.
            return (-1);
        }
    }

    while (lst)
	{
        if (i < size)
		{
            if (pipe(fd) == -1)
			{
                perror("pipe error");
                free(pid); // Libérer la mémoire en cas d'erreur.
                return (-1);
            }
            pid[i] = fork();
            if (pid[i] < 0)
			{
                perror("fork error");
                free(pid); // Libérer la mémoire en cas d'erreur.
                return (-1);
            }

            if (pid[i] == 0)
			{ // Processus enfant
                if (lst != last)
				{
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]); // Fermer l'entrée du pipe
                    close(fd[1]); // Fermer l'écriture du pipe après avoir dupé
                }

                if (lst->path_cmd != NULL) \
				{
                    execve(lst->path_cmd, lst->arr, lst->env);
                }
                r = err_msg(lst->path_cmd, lst->arr[0]);
                perror("minishell");
                exit(r);
            }
			else
			{ // Processus parent
                if (lst != last)
				{
                    dup2(fd[0], 0); // Redirige l'entrée standard
                }
                close(fd[1]); // Fermer l'écriture sur le pipe
                close(fd[0]); // Fermer la lecture sur le pipe
            }

            i++;
        }
        lst = lst->next;
    }

    for (int j = 0; j < i; j++)
	{
        int status;
        waitpid(pid[j], &status, 0); // Attendre chaque processus fils
        r = WEXITSTATUS(status); // Récupérer le code de retour
    }
    dup2(fd0, 0); // Rétablir l'entrée standard
    dup2(fd1, 1); // Rétablir la sortie standard
    
    free(pid); // Libérer la mémoire allouée
    return r; // Retourner le code de sortie
}