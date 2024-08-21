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

	fd = open(path, O_WRONLY);
	f = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arr, 2);
    if (path == NULL && strchr(arr, '/') == NULL)
        ft_putstrn_fd(": command not found", 2);
	else if ((fd == -1 && f == NULL) || (strchr(arr, '/') != NULL))
		ft_putstrn_fd(": No such file or directory", 2);
	else if (fd == -1 && f != NULL)
		ft_putstrn_fd(": is a directory", 2);
	else if (fd != -1 && f == NULL)
		ft_putstrn_fd(" permission denied", 2);
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
void print_s_files(t_list *list) {
    int i = 0;

    while (list)
    {
        i = 0;
        while (i < list->num_of_files)
        {
            // if (list != NULL && list->files != NULL) {
            //     printf("File Name: %s\n", list->files[i].file_name);
            //     printf("Heredoce Name: %s\n", list->files[i].heredoce_name);
            //     printf("Type: %d\n", list->files[i].type);
            //     printf("File Descriptor: %d\n", list->files[i].fd);
            //     printf("Error File: %d\n", list->files[i].error_file);
            //     printf("\n----------------------\n");
            // } else {
            //     printf("No files in list.\n");
            // }
            i++;
        }
        printf("Last in = %d\n", list->in);
        printf("Last out = %d\n", list->out);
    list = list->next;
    }
}

int open_files(t_list **node)
{
    int i;
    t_list *tmp;

    tmp = *node;
    while (tmp)
    {
        i = 0;
        while (i < tmp->num_of_files)
        {
            if (tmp->files[i].error_file == -1)
            {
                printf("minishell : %s: ambiguous redirect\n", tmp->files[i].file_name);
                return (-1);
            }
            if (access(tmp->files[i].file_name, F_OK) == 0 && access(tmp->files[i].file_name, R_OK | W_OK) == -1)
            {
                printf("minishell : %s: Permission denied\n", tmp->files[i].file_name);
                g_status = 1;
                return (-1);
            }
            if (tmp->files[i].type == REDIRECT_INPUT)
            {
                if (access(tmp->files[i].file_name, F_OK) == 0 && tmp->files[i].file_name[0] != '$')
                {
                    tmp->files[i].fd = open(tmp->files[i].file_name, O_RDWR | O_TRUNC, 0644);
                }
                else
                {
                    printf("minishell : %s: No such file or directory\n", tmp->files[i].file_name);
                    return (-1);
                }
            }
            else if (tmp->files[i].type == REDIRECT_APPEND)
                tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
            else if (tmp->files[i].type == REDIRECT_OUTPUT)
                tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
            else
                tmp->files[i].fd = open(tmp->files[i].heredoce_name, O_CREAT | O_RDWR | O_APPEND, 0644);
            if (tmp->files[i].type >= 5 && tmp->files[i].type <= 6)
                tmp->out = tmp->files[i].fd;
            else if (tmp->files[i].type >= 7 && tmp->files[i].type <= 8)
                tmp->in = tmp->files[i].fd;
            i++;
        }
        tmp = tmp->next;
    }
    return (0);
}

int ft_exe(t_list *lst, t_env *env)
{
    int *pid;
    int j = 0;
    t_list *last;
    // int fd[2];
    // int fd0;
    // int fd1;
    // fd0 = dup(0);
    // fd1 = dup(1);
    
    int size = ft_lstsize(lst);
    pid = malloc(size * sizeof(int));
    if (!pid) {
        perror("malloc error");
        return (-1);
    }

    if (open_files(&lst) == -1)
    {
        g_status = 1;
        return (g_status);
    }

    if (ft_lenarray(lst->arr) == 0 && lst->path_cmd == NULL)
    {
        return (g_status);
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
            // if (pipe(fd) == -1)
			// {
            //     perror("pipe error");
            //     free(pid);
            //     return (-1);
            // }
            signal(SIGINT, SIG_IGN);
            pid[i] = fork();
            if (pid[i] < 0)
			{
                perror("fork error");
                free(pid);
                return (-1);
            }

            if (pid[i] == 0)
			{
                signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                // handle_pipe();
                g_status = 0;
                // if (lst != last)
				// {
                //     dup2(fd[1], lst->out);
                //     close(fd[0]);
                //     close(fd[1]);
                // }
                if (link_builtin(lst, env) == 1)
                {
                    free(pid);
                    // break;
                    exit (g_status);
                }
                else
                {
                    if (lst->path_cmd == NULL && !lst->arr[0])
                        return (0);
                    if (lst->path_cmd != NULL)
                    {
                        execve(lst->path_cmd, lst->arr, lst->envr);
                    }
                    g_status = err_msg(lst->path_cmd, lst->arr[0]);
                    
                    exit(g_status);

                }
            }
			else
			{
                // if (lst != last)
				// {
                //     dup2(fd[0], 0);
                // }
                // close(fd[1]);
                // close(fd[0]);
            }

            i++;
        }
        lst = lst->next;
    }

    while (j < i)
	{
        waitpid(pid[j++], &g_status, 0);
        g_status = WEXITSTATUS(g_status);
        // signal(SIGINT, sig_handle);
    }
    // dup2(fd0, 0);
    // dup2(fd1, 1);

    free(pid);
    return (g_status);
}

