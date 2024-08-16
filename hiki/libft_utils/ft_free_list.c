#include "minishell.h"


void free_lst_lexer(t_lexer **head)
{
	t_lexer *tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->data);
		free((*head));
		*head = tmp;
	}
}

void free_lst_env(t_env **env)
{
	t_env *tmp;

	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->bfr_eql);
		free((*env)->after_eql);
		free((*env));
		*env = tmp;
	}
}
void free_list(t_list **lst)
{
    t_list *temp;

    while (*lst != NULL)
	{
        temp = *lst;
        *lst = (*lst)->next;
        int i = 0;
        while (temp->arr[i] != NULL)
		{
            free(temp->arr[i]);
            i++;
        }
        free(temp->arr);
        free(temp->path_cmd);
        free(temp);
		free(temp->last_infile);
		free(temp->last_outfile);
    }
}
