#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_list{
	char *data;
	struct s_list *next;
} t_list;


/*						 libft							*/
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *data);
int	ft_strlen(char *str);
void	ft_bzero(char *str, int n);

/*						parsing							*/
void ft_start(t_list *head, char *line);

#endif