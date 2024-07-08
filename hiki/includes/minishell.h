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

// typedef enum {
// 	command = 0,
// 	file	= 1,
// }
/*						 libft							*/
t_list	*ft_lstnew(char *data);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_strlen(char *str);
void	ft_bzero(char *str, int n);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start, int len);

/*						utils							*/
int get_index(char *line, char *str);
char *ft_str_alloc(char *line, int size);

/*						parsing							*/
t_list *ft_start(t_list *head, char *line);

#endif