/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:07:57 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/23 15:54:50 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_close_fds(t_list **lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (i < tmp->num_of_files)
		{
			if (tmp->files[i].error_file == -1)
				break ;
			if (tmp->files[i].fd != tmp->in && tmp->files[i].fd != tmp->out)
				close(tmp->files[i].fd);
			else if ((tmp->files[i].fd == tmp->in || 
					tmp->files[i].fd == tmp->out)
				&& (tmp->error == false || (ft_lenarray((*lst)->arr) == 0 && 
						(*lst)->path_cmd == NULL)))
				close(tmp->files[i].fd);
			i++;
		}
		tmp = tmp->next;
	}
}

int	wait_process(int *pid, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		waitpid(pid[j++], &g_status, 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = WTERMSIG(g_status) + 128;
		signal(SIGINT, sig_handle);
	}
	free(pid);
	return (g_status);
}

void	setup_next_pipe(t_list *lst)
{
	if (lst->next)
		lst->next->prev_in = lst->pipe_fd[0];
	if (lst->in != 0)
		close(lst->in);
	if (lst->out != 1)
		close(lst->out);
	return ;
}

void	void_comnd(t_list **lst)
{
	ft_close_pr(*lst);
	setup_next_pipe(*lst);
	*lst = (*lst)->next;
	return ;
}

int	lst_handle(t_list *lst, int *pid, int size, int *i)
{
	while (lst)
	{
		if ((*i) < size)
		{
			signal(SIGINT, SIG_IGN);
			if (lst->next)
				pipe(lst->pipe_fd);
			if (ft_lenarray(lst->arr) == 0)
			{
				void_comnd(&lst);
				continue ;
			}
			pid[(*i)] = fork();
			if (pid[(*i)] < 0)
				return (-2);
			if (pid[(*i)] == 0)
				child_process(lst, pid);
			else
				ft_close_pr(lst);
			(*i)++;
		}
		setup_next_pipe(lst);
		lst = lst->next;
	}
	return (0);
}
