#include "minishell.h"

char *generate_heredoc_name(void)
{
	static int i;
	char *num;
	char *name;

	i++;
	num = ft_itoa(i);
	name = ft_strjoin("/tmp/heredoc_", num);

	return (name);
}

static void handler_input(t_lexer **lexer, t_list **lst, int i)
{
	(*lexer) = (*lexer)->next;
	(*lst)->files[i].file_name = ft_strdup((*lexer)->data);
	// if ((*lexer)->prev->type == REDIRECT_INPUT)
		// njrb access bach ndir each kayn file ola la
	if ((*lexer)->prev->type == HEREDOC)
		(*lst)->files[i].fd = open(generate_heredoc_name(), O_CREAT | O_RDWR , 0644);
	(*lst)->in = (*lst)->files[i].fd;
}

static void handler_output(t_lexer **lexer, t_list **lst, int i)
{
	(*lexer) = (*lexer)->next;
	(*lst)->files[i].file_name = ft_strdup((*lexer)->data);

	if ((*lexer)->prev->type == REDIRECT_APPEND)
		(*lst)->files[i].fd = open((*lexer)->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		(*lst)->files[i].fd = open((*lexer)->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	(*lst)->out = (*lst)->files[i].fd;
}

// void heredoce_start(t_list **node, t_env **env)
// {
// 	char *str;
// 	int fd;

// 	while (str != NULL && ft_strcmp(str, (*node)->files))
// }

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
		if (lextmp->type == REDIRECT_OUTPUT || lextmp->type == REDIRECT_APPEND)
		{
			tmp->files[i].type = lextmp->type;
			handler_output(&lextmp, &tmp, i);
			i++;
		}
		else if (lextmp->type == HEREDOC || lextmp->type == REDIRECT_INPUT)
		{
			tmp->files[i].type = lextmp->type;
			handler_input(&lextmp, &tmp, i);
			if (lextmp->type == HEREDOC)
				
			i++;
		}
		lextmp = lextmp->next;
	}
	return (0);
}
			//khasni ntchecki wach heredoc bach n3rf fin n7to ola wach file kayn ola la;
			// < file kahsni nchof wach file kayn ila kan ndir fiha dakchi li kahs idar
			// << EOF ndir file f tmp o njm3 fih output b getnextline  o dik EOF hhiya bach atsala lktba
			// >> && > dima katgad lihom file