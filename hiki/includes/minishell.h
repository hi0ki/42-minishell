#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

#define WORD 1                // For general words, command names, arguments, etc.
#define PIPE 2                // For the pipe symbol '|'
#define REDIRECT_INPUT 3      // For input redirection '<'
#define REDIRECT_OUTPUT 4     // For output redirection '>'
#define REDIRECT_APPEND 5     // For append output redirection '>>'
#define HEREDOC 6             // For here-document '<<'
#define SINGLE_QUOTE 7        // For single quotes '''
#define DOUBLE_QUOTE 8        // For double quotes '"'
#define DOLLAR 9              // For variable expansion '$'
#define BUILTIN_CD 10         // Built-in command: cd
#define BUILTIN_ECHO 11       // Built-in command: echo
#define BUILTIN_ENV 12        // Built-in command: env
#define BUILTIN_EXIT 13       // Built-in command: exit
#define BUILTIN_EXPORT 14     // Built-in command: export
#define BUILTIN_PWD 15        // Built-in command: pwd
#define BUILTIN_UNSET 16      // Built-in command: unset
#define SPACE 17              // For space character ' '


typedef struct s_lexer{
	char			*data;
	int				type;
	struct s_lexer	*next;
    struct s_lexer	*prev;
} t_lexer;

typedef struct s_env{
	char			*bfr_eql;
	char			*after_eql;
	int				env;
	struct s_env	*next;
}	t_env;

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
char    *ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, int start, int len);

/*						utils for lexer							*/
t_lexer	*lexer_lstnew(char *data);
void	lexer_add_back(t_lexer **lst, t_lexer *new);
char	*ft_str_alloc(char *line, int size);
char	*alloc_special_char(char *line);
int		check_special_char(char *str);
int		get_index(char *line, char *str);
int		ft_handle_quotes(char *line);
/*						lexer type utils						*/
void set_type(t_lexer **head);


/*						parsing							*/
t_lexer *ft_start(t_lexer *head, char *line);


/*						builtin							*/
void	env_init(t_env **env, char **envr);
int    ft_cd(char **av, t_env *env);
int	ft_strcmp(char *s1, char *s2);
#endif