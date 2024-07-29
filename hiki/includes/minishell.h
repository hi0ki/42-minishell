/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:03:08 by mel-hime          #+#    #+#             */
/*   Updated: 2024/07/21 10:03:11 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define CMD	1
#define ARG 2
#define PIPE 3                // For the pipe symbol '|'
#define WORD 4                // For general words, command names, arguments, etc.
#define REDIRECT_INPUT 5      // For input redirection '<'
#define REDIRECT_OUTPUT 6     // For output redirection '>'
#define REDIRECT_APPEND 7     // For append output redirection '>>'
#define HEREDOC 8             // For here-document '<<'
#define SQUOTE 9        // For single quotes '''
#define DQUOTE 10        // For double quotes '"'
#define DOLLAR 11              // For variable expansion '$'
#define BUILTIN_CD 12         // Built-in command: cd
#define BUILTIN_ECHO 13       // Built-in command: echo
#define BUILTIN_ENV 14        // Built-in command: env
#define BUILTIN_EXIT 15       // Built-in command: exit
#define BUILTIN_EXPORT 16     // Built-in command: export
#define BUILTIN_PWD 17        // Built-in command: pwd
#define BUILTIN_UNSET 18      // Built-in command: unset
#define SPACE 19              // For space character ' '

typedef struct s_lexer{
	char			*data;
	int				type;
	int				var_quotes;
	int				len;
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
	char *path_cmd;
	char **arr;
	struct s_list	*next;
} t_list;


void shell(t_list **lst, char **env);
/*						 libft							*/
t_list	*ft_lstnew(void);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_strlen(char *str);
void	ft_bzero(char *str, int n);
char	*ft_strdup(char *s1);
char    *ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
int		ft_isalpha(int c);
char	*ft_substr(char *s, int start, int len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstrn_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2,int n);
void	free_lst_lexer(t_lexer **head);
void	free_lst_env(t_env **env);
void 	free_list(t_list **lst);
char    *ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);

/*					lexer & set_tyep &utils_lexer			*/
t_lexer *start_lexer(t_lexer *head, char *line);
t_lexer	*lexer_lstnew(char *data);
void	lexer_add_back(t_lexer **lst, t_lexer *new);
char	*ft_str_alloc(char *line, int size);
char	*alloc_special_char(char *line);
int		check_special_char(char *str);
int		get_index(char *line, char *str);
int		ft_handle_quotes(char *line);
void 	set_type(t_lexer **head);

/*						parsing							*/
void start_parsing(t_lexer **head, t_env *env);
void fill_variables(t_lexer **head, t_env *env);
void join_nodes(t_lexer **head);
void create_lst(t_list **lst, t_lexer **head, t_env **env);
void parsing_type(t_lexer **head);
/*						parisng utils				*/
int count_cmd(t_lexer *head);
int size_node(t_lexer *head);

/*						env 						*/
char *get_value_env(t_env *env, char *av);


/*						builtin && utils builtin							*/
int    	ft_cd(char **av, t_env *env);
void	ft_echo(int ac, char **av);
int		ft_export(char **av, t_env *env);
void    print_all_env(t_env *env);
int		ft_env(t_env *env);
void	env_init(t_env **env, char **envr);
void	ft_envaddback(t_env **head, t_env *new);
t_env	*ft_envnew(char *s);

#endif


/*

t_file
name[] 
type in ou heredoc append

cmd[] -> word word 
file 



*/