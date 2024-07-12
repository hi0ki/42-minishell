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
	char			*data;
	int				type;
	struct s_list	*next;
} t_list;

/*						 libft							*/
t_list	*ft_lstnew(char *data);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_strlen(char *str);
void	ft_bzero(char *str, int n);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start, int len);

/*						utils for lexer							*/
char	*ft_str_alloc(char *line, int size);
char	*alloc_special_char(char *line);
int		check_special_char(char *str);
int		get_index(char *line, char *str);
int		ft_handle_quotes(char *line);

/*						parsing							*/
t_list *ft_start(t_list *head, char *line);

#endif