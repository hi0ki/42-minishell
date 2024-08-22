/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:07:57 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/22 22:10:27 by mel-hime         ###   ########.fr       */
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

