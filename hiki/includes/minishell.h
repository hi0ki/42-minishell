/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:03:08 by mel-hime          #+#    #+#             */
/*   Updated: 2024/08/23 16:13:06 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include "/goinfre/eel-ansa/homebrew/opt/readline/include/readline/history.h"
# include "/goinfre/eel-ansa/homebrew/opt/readline/include/readline/readline.h"
# include <readline/readline.h>
# include <readline/history.h>

# define CMD 1
# define ARG 2
# define PIPE 3
# define WORD 4
# define REDIRECT_OUTPUT 5
# define REDIRECT_APPEND 6
# define REDIRECT_INPUT 7
# define HEREDOC 8
# define SQUOTE 9
# define DQUOTE 10
# define DOLLAR 11
# define SPC 19

int	g_status;

typedef struct s_files{
	char	*file_name;
	char	*heredoce_name;
	bool	heredoce_expand;
	int		type;
	int		fd;
	int		error_file;
}	t_files;

typedef struct s_lexer
{
	char			*data;
	int				type;
	int				error_quotes;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_env{
	char			*bfr_eql;
	char			*after_eql;
	int				env;
	struct s_env	*next;
}	t_env;

typedef struct s_list{
	char			*path_cmd;
	char			**arr;
	char			**envr;
	t_env			**env;
	int				num_of_files;
	t_files			*files;
	int				pipe_fd[2];
	int				in;
	int				out;
	int				prev_in;
	bool			error;
	struct s_list	*next;
}	t_list;

/*						GNL								*/
void	print_list(t_lexer *head);
char	*get_next_line(int fd);
/*						 libft							*/
t_list	*ft_lstnew(void);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_strlen(char *str);
void	ft_bzero(char *str, int n);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*ft_substr(char *s, int start, int len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstrn_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strjoin3(char *s1, char *s2);
char	**ft_split(char *s, char *c);
char	*ft_itoa(int n);
int		ft_lstsize(t_list *lst);
int		ft_envsize(t_env *env);
t_list	*ft_lstlast(t_list *lst);
void	ft_free_arr(char **array);
void	free_lst_lexer(t_lexer **head);
void	free_lst_env(t_env **env);
void	free_list(t_list **lst);
void	free_files(t_files *file, int num_of_files);
void	*ft_calloc(size_t count, size_t size);
int		ft_lenarray(char **array);

/*						Error handler						*/
int		error_handler(t_lexer *lexer);
/*					lexer & set_tyep &utils_lexer			*/
t_lexer	*start_lexer(t_lexer *head, char *line);
t_lexer	*lexer_lstnew(char *data);
void	lexer_add_back(t_lexer **lst, t_lexer *new);
char	*ft_str_alloc(char *line, int size);
char	*alloc_special_char(char *line);
int		check_special_char(char *str);
int		get_index(char *line, char *str);
int		ft_handle_quotes(char *line);
void	set_type(t_lexer **head);

/*						parsing							*/
void	start_parsing(t_lexer **head, t_env *env);
void	fill_variables(t_lexer **head, t_env *env);
void	join_nodes(t_lexer **head);
void	create_lst(t_list **lst, t_lexer **head, t_env **env, char **envr);
void	parsing_type(t_lexer **head);
/*						parisng utils				*/
int		count_cmd(t_lexer *head);
int		size_node(t_lexer *head);
void	num_of_files(t_list **lst, t_lexer **lexer);
int		get_name_index(t_lexer **node, int j, int i);
char	*edit_data(char *value, char *old_value, int i, int j);
char	*get_value_env(t_env *env, char *av);
void	delete_var(t_lexer **node);
int		valid_to_split(t_lexer *node);
/*					check utils						*/
int		check_oper(t_lexer *node);
int		check_variable(t_lexer *node);
/*					fill files						*/
void	fill_variables(t_lexer **head, t_env *env);
int		fill_files(t_list **lst, t_lexer **lexer, t_env **env);
void	fill_arr(t_list **lst, t_lexer **head, int size);
void	fill_path(t_list **lst, t_env **env, char **envr);
/*					heredoc							*/
void	heredoce_start(t_files *file, t_env **env);
char	*expand_for_heredoc(char *str, int i, int j, t_env **env);
/*						env 						*/
char	*get_value_env(t_env *env, char *av);

/*						builtin && utils builtin							*/
int		ft_cd(char **av, t_env *env);
int		ft_echo(int ac, char **av, int fd_out);
int		ft_exit(char **av);
int		ft_pwd(int fd_out);
int		ft_export(char **av, t_env **env, int fd_out);
int		ft_unset(char **av, t_list **lst);
void	print_all_env(t_env *env, int fd_out);
int		ft_env(t_env *env, int fd_out);
void	env_init(t_env **env, char **envr);
void	ft_envaddback(t_env **head, t_env *new);
t_env	*ft_envnew(char *s);
int		link_builtin(t_list *lst);
/*						execution	*/
int		err_msg(char *path, char *arr);				

int		ft_exe(t_list *lst);

/*         signals	*/
void	sig_handle(int sig);

/*            norm		*/
char	**env_to_tab(t_env *env);
int		go_path(int opt, t_env *env);
char	*get_path(t_env *env, char *key);
int		add_oldpwd(t_env *env);
void	print_all_env(t_env *env, int fd_out);
int		err_msg(char *path, char *arr);
void	ft_close_fds(t_list **lst);
int		wait_process(int *pid, int i);
void	setup_next_pipe(t_list *lst);
void	ft_close_pr(t_list *lst);
int		lst_handle(t_list *lst, int *pid, int size, int *i);
int		child_process(t_list *lst, int *pid);

#endif