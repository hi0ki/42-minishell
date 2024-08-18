#include "minishell.h"

char *generate_heredoc_name(void)
{
	static int i;
	char *num;
	char *name;

	i++;
	num = ft_itoa(i);
	name = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (name);
}

// static void handler_input(t_lexer **lexer, t_list **lst, int i)
// {
// 	(*lexer) = (*lexer)->next;
// 	if ((*lexer)->prev->type == REDIRECT_INPUT)
// 	{
// 		if (access((*lexer)->data, F_OK) != -1)
// 			(*lst)->files[i].fd = open(generate_heredoc_name(), O_CREAT | O_RDWR , 0644);
// 		else
// 		{
// 			(*lst)->files[i].fd = -1;
// 			(*lst)->files[i].file_name = NULL;
// 			return ;
// 		}
// 	}
// 	if ((*lexer)->prev->type == HEREDOC)
// 		(*lst)->files[i].fd = open(generate_heredoc_name(), O_CREAT | O_RDWR , 0644);
// 	(*lst)->files[i].file_name = ft_strdup((*lexer)->data);
// 	(*lst)->in = (*lst)->files[i].fd;
// }

// static void handler_output(t_lexer **lexer, t_list **lst, int i)
// {
// 	(*lexer) = (*lexer)->next;
// 	(*lst)->files[i].file_name = ft_strdup((*lexer)->data);

// 	if ((*lexer)->prev->type == REDIRECT_APPEND)
// 		(*lst)->files[i].fd = open((*lexer)->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	else
// 		(*lst)->files[i].fd = open((*lexer)->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	(*lst)->out = (*lst)->files[i].fd;
// }

void heredoce_start(t_files *file, t_env **env)
{
	char *str;
	int fd;
	char *name;

	name = generate_heredoc_name();
	fd = open(name , O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file->fd == -1)
	{
		perror(file->file_name);
		exit(1); // nzid return bach may endich l process
	}
	write(1, "> ", 2);
	str = get_next_line(0);
	while (str != NULL && ft_strcmp(str, file->file_name) != 0)
	{
		write(fd, str, ft_strlen(str));
		free(str);
		write(1, "> ", 2);
		str = get_next_line(1);
	}
	close(fd);
	file->heredoce_name= ft_strdup(name);
	free(str);
	free(name);
}

int fill_files(t_list **lst, t_lexer **lexer, t_env **env)
{
	t_list *tmp;
	t_lexer *lextmp;
	int i;

	tmp = *lst;
	lextmp = *lexer;
	tmp->files = malloc (tmp->num_of_files * sizeof(t_files));
	i = 0;
	while (lextmp && tmp)
	{
		if (lextmp->type == PIPE)
		{
			tmp = tmp->next;
			i = 0;
			tmp->files = malloc (tmp->num_of_files * sizeof(t_files));
		}
		if (lextmp->type >= 5 && lextmp->type <= 8)
		{
			tmp->files[i].type = lextmp->type;
			if (lextmp->type == HEREDOC)
			{
				tmp->files[i].file_name = ft_strjoin(lextmp->next->data, "\n");
				heredoce_start(&tmp->files[i], env);
			}
			else
				tmp->files[i].file_name = ft_strdup(lextmp->next->data);
			i++;
		}
		lextmp = lextmp->next;
	}
	return (0);
}
