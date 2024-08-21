/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:08:20 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/21 19:39:46 by mel-hime         ###   ########.fr       */
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
	// printf ("i = %d\n",i);
	while (j <i)
	{
		waitpid(pid[j], &g_status, 0);
		j++;
	}
	// printf("******1111\n");
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
                    tmp->files[i].fd = open(tmp->files[i].file_name, O_RDONLY, 0644);
                }
                else
                {
                    printf("minishell : %s: No such file or directory\n", tmp->files[i].file_name);
                    return (-1);
                }
            }
            else if (tmp->files[i].type == REDIRECT_APPEND)
                tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
            else if (tmp->files[i].type == REDIRECT_OUTPUT)
                tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
void ft_close_fds(t_list **lst)
{
    t_list *tmp;
    int i;

    i = 0;
    tmp = *lst;
    while (tmp)
    {
        i = 0;
        while (i < tmp->num_of_files)
        {
            if (tmp->files[i].fd != tmp->in && tmp->files[i].fd != tmp->out)
                close(tmp->files[i].fd);
            i++;
        }
        tmp = tmp->next;
    }
}
// void    handle_pipe(t_list lst)
// {}

int ft_exe(t_list *lst, t_env *env)
{
    int *pid;
    int j = 0;
    t_list *last;
    
    int size = ft_lstsize(lst);
    pid = malloc(size * sizeof(int));
    if (!pid)
        return (perror("malloc error"), -1);
    if (open_files(&lst) == -1)
        return (g_status = 1, g_status);
    else
        ft_close_fds(&lst);
    int i = 0;
    last = ft_lstlast(lst);
    
    if (size == 1) {
        if (link_builtin(lst, env) == 1)
            return (free(pid), g_status);
    }

    while (lst)
	{
        
        if (i < size)
		{
            signal(SIGINT, SIG_IGN);
            if(lst->next)
                pipe(lst->pipe_fd);
            pid[i] = fork();
            if (pid[i] < 0)
                return (perror("fork error"), free(pid), -1);
            if (pid[i] == 0)
			{
                signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                g_status = 0;
                if (lst->in != 0)
				    dup2(lst->in, 0);
                else if (lst->prev_in != 0)
                    dup2(lst->prev_in, 0);
                if (lst->out != 1)
				    dup2(lst->out, 1);
                else if (lst->next)
                    dup2(lst->pipe_fd[1], 1);
                if (link_builtin(lst, env) == 1)
                    return (free(pid), exit(g_status), 1);
                else
                {
                    if (lst->path_cmd == NULL && !lst->arr[0])
                        return (0);
                    if (lst->path_cmd != NULL)
                        execve(lst->path_cmd, lst->arr, lst->envr);
                    g_status = err_msg(lst->path_cmd, lst->arr[0]);
                    exit(g_status);
                }
            }
			else
			{
                if (lst->prev_in != 0)
                    close (lst->prev_in);
                if (lst->next)
                    close (lst->pipe_fd[1]);
            }
            i++;
        }
        if (lst->next)
            lst->next->prev_in = lst->pipe_fd[0];
        if (lst->in != 0)
            close(lst->in);
        if (lst->out != 1)
            close(lst->out);
        lst = lst->next;
    }
    while (j < i)
	{
        waitpid(pid[j++], &g_status, 0);
        g_status = WEXITSTATUS(g_status);
        signal(SIGINT, sig_handle);
    }
    return (free(pid), g_status);
}

