#include "minishell.h"

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
			{
				if (lextmp->next->data[0] == '$' && ft_strlen(lextmp->next->data))
					tmp->files[i].error_file = -1;
				tmp->files[i].file_name = ft_strdup(lextmp->next->data);
			}
			i++;
		}
		lextmp = lextmp->next;
	}
	return (0);
}
