#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef enum TokenType {
    WORD = 1,
    PIPE = 2,
    REDIRECT_INPUT = 3,
    REDIRECT_OUTPUT = 4,
    REDIRECT_APPEND = 5,
    HEREDOC = 6,
    SEMICOLON = 7,
    AND_IF = 8,
    OR_IF = 9,
    PARENTHESIS_OPEN = 10,
    PARENTHESIS_CLOSE = 11,
    SINGLE_QUOTE = 12,
    DOUBLE_QUOTE = 13,
    DOLLAR = 14,
    BACKSLASH = 15,
    NEWLINE = 16,
    // EOF = 17,
    ASSIGNMENT = 18,
    WILDCARD = 19
} e_token;

typedef struct s_lexer{
	char			*data;
	int				type;
	struct s_lexer	*next;
} t_lexer;

typedef struct s_list{
	char			*data;
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
void	lexer_add_back(t_lexer **lst, t_lexer *new);
t_lexer	*lexer_lstnew(char *data);
char	*ft_str_alloc(char *line, int size);
char	*alloc_special_char(char *line);
int		check_special_char(char *str);
int		get_index(char *line, char *str);
int		ft_handle_quotes(char *line);

/*						parsing							*/
t_lexer *ft_start(t_lexer *head, char *line);

#endif