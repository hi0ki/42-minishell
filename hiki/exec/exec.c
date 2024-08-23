/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:08:20 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/23 15:56:33 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_handler(t_list *tmp, int i)
{
	if (tmp->files[i].type == REDIRECT_INPUT)
		tmp->files[i].fd = open(tmp->files[i].file_name, O_RDONLY, 0644);
	else if (tmp->files[i].type == REDIRECT_APPEND)
		tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | 
				O_WRONLY | O_APPEND, 0644);
	else if (tmp->files[i].type == REDIRECT_OUTPUT)
		tmp->files[i].fd = open(tmp->files[i].file_name, O_CREAT | 
				O_WRONLY | O_TRUNC, 0644);
	else
		tmp->files[i].fd = open(tmp->files[i].heredoce_name, O_CREAT | 
				O_RDWR | O_APPEND, 0644);
	if (tmp->files[i].fd < 0)
	{
		tmp->error = false;
		tmp->files[i].error_file = -1;
		ft_putstr_fd("minishell : ", 2);
		perror(tmp->files[i].file_name);
		g_status = 1;
		return (-1);
	}
	else if (tmp->files[i].type >= 5 && tmp->files[i].type <= 6)
		tmp->out = tmp->files[i].fd;
	else if (tmp->files[i].type >= 7 && tmp->files[i].type <= 8)
		tmp->in = tmp->files[i].fd;
	return (0);
}

static void	open_files(t_list **node)
{
	int		i;
	t_list	*tmp;

	tmp = *node;
	while (tmp)
	{
		i = 0;
		while (i < tmp->num_of_files)
		{
			if (tmp->files[i].error_file == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp->files[i].file_name, 2);
				ft_putstrn_fd(": ambiguous redirect", 2);
				tmp->error = false;
				g_status = 1;
				break ;
			}
			if (open_handler(tmp, i) == -1)
				break ;
			i++;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	pipe_handle(t_list *lst)
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

int	child_process(t_list *lst, int *pid)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

int	ft_exe(t_list *lst)
{
	int	*pid;
	int	i;
	int	size;

	size = ft_lstsize(lst);
	i = 0;
	open_files(&lst);
	ft_close_fds(&lst);
	if (ft_lenarray(lst->arr) == 0 && lst->path_cmd == NULL)
		return (g_status);
	pid = malloc(size * sizeof(int));
	if (!pid)
		return (perror("malloc error"), -1);
	if (size == 1 && lst->error == true)
	{
		if (link_builtin(lst) == 1)
			return (free (pid), g_status);
	}
	else if (size == 1 && lst->error == false)
		return (free(pid), g_status);
	if (lst_handle(lst, pid, size, &i) == -2)
		return (perror("fork error"), free(pid), -1);
	wait_process(pid, i);
	return (g_status);
}
