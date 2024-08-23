/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:08:20 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/23 14:44:04 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_s_files(t_list *list) {
//     int i = 0;

//     while (list)
//     {
//         i = 0;
//         while (i < list->num_of_files)
//         {
//             // if (list != NULL && list->files != NULL) {
//             //     printf("File Name: %s\n", list->files[i].file_name);
//             //     printf("Heredoce Name: %s\n", list->files[i].heredoce_name);
//             //     printf("Type: %d\n", list->files[i].type);
//             //     printf("File Descriptor: %d\n", list->files[i].fd);
//             //     printf("Error File: %d\n", list->files[i].error_file);
//             //     printf("\n----------------------\n");
//             // } else {
//             //     printf("No files in list.\n");
//             // }
//             i++;
//         }
//         printf("Last in = %d\n", list->in);
//         printf("Last out = %d\n", list->out);
//     list = list->next;
//     }
// }

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
                tmp->error = false;
                g_status = 1;
                break ;
            }
            if (tmp->files[i].type == REDIRECT_INPUT)
            {
                tmp->files[i].fd = open(tmp->files[i].file_name, O_RDONLY, 0644);
            }
            else if (tmp->files[i].type == REDIRECT_APPEND)
                tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
            else if (tmp->files[i].type == REDIRECT_OUTPUT)
                tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            else
                tmp->files[i].fd = open(tmp->files[i].heredoce_name, O_CREAT | O_RDWR | O_APPEND, 0644);
            if (tmp->files[i].fd < 0)
            {
                tmp->error = false;
                ft_putstr_fd("minishell : ", 2);
                perror(tmp->files[i].file_name);
                g_status = 1;
                break ;
            }
            else if (tmp->files[i].type >= 5 && tmp->files[i].type <= 6)
                tmp->out = tmp->files[i].fd;
            else if (tmp->files[i].type >= 7 && tmp->files[i].type <= 8)
                tmp->in = tmp->files[i].fd;
            i++;
        }
        if (tmp)
            tmp = tmp->next;
    }
    return (0);
}

void    pipe_handle(t_list *lst)
{
    if (lst->in != 0)
        dup2(lst->in, 0);
    else if (lst->prev_in != 0)
    {
        dup2(lst->prev_in, 0);
        close(lst->prev_in);
    }
    if (lst->out != 1)
        dup2(lst->out, 1);
    else if (lst->next)
    {
        dup2(lst->pipe_fd[1], 1);
        close(lst->pipe_fd[1]);
        close(lst->pipe_fd[0]);
    }
    return ;
}

int child_process(t_list *lst, int *pid)
{
    // signal(SIGINT, SIG_DFL);
    // signal(SIGQUIT, SIG_DFL);
    g_status = 0;
    pipe_handle(lst);
    if (link_builtin(lst) == 1)
    {
        free(pid);
        exit (g_status);
    }
    else
    {
        if (lst->path_cmd == NULL && !lst->arr[0])
            return (0);
        if (lst->path_cmd != NULL)
            execve(lst->path_cmd, lst->arr, lst->envr);
        g_status = err_msg(lst->path_cmd, lst->arr[0]);
        exit(g_status);
    }
    return (1);
}

int ft_exe(t_list *lst, t_env *env)
{
    int *pid;
    int i;
    int size = ft_lstsize(lst);
    
    i = 0;
    open_files(&lst);
    // ft_close_fds(&lst);
    if (ft_lenarray(lst->arr) == 0 && lst->path_cmd == NULL)
        return (g_status);
    pid = malloc(size * sizeof(int));
    if (!pid)
        return(perror("malloc error"), -1);
    if (size == 1 && lst->error == true)
    {
        if (link_builtin(lst) == 1)
            return (free (pid), g_status);
    }
    else if (size == 1 && lst->error == false)
        return (free(pid) ,g_status);
    if ( lst_handle(lst, pid, size, &i) == -2)
        return (perror("fork error"), free(pid), -1);
    wait_process(pid, i);
    return (g_status);
}


