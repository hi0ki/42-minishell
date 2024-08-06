#include "minishell.h"

void link_builtin(t_list *lst, t_env *env)
{
	if (ft_strcmp(lst->arr[0], "cd") == 0)
	{
		ft_cd(lst->arr, env);
	}
	else if (ft_strcmp(lst->arr[0], "echo") == 0)
	{
		ft_echo(2, lst->arr);
	}
	else if (ft_strcmp(lst->arr[0], "env") == 0)
	{
		ft_env(env);
	}
	else if (ft_strcmp(lst->arr[0], "export") == 0)
	{
	printf("hna\n");
		ft_export(lst->arr, env);
	}
	else 
		// startexe
}