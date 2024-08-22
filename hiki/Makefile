SRC = 	main.c\
		../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c \
		parsing/parsing.c parsing/fill_variables.c parsing/join_data.c parsing/create_lst.c parsing/parsing_utils.c parsing/parsing_type.c \
		parsing/fill_files.c parsing/fill_array.c parsing/fill_path.c parsing/heredoc.c parsing/utils_variables.c\
		lexer/utils_lexer.c lexer/lexer.c lexer/token_type.c lexer/error_handler.c  lexer/check_operators.c\
		builtin/cd.c builtin/init_env.c builtin/echo.c builtin/env.c builtin/export.c builtin/pwd.c builtin/unset.c builtin/exit.c \
		exec/exec.c exec/link_builtin.c builtin/builtin_utils.c \

LIBFT = libft_utils/ft_lstadd_back.c libft_utils/ft_lstnew.c \
		libft_utils/ft_strlen.c libft_utils/ft_bzero.c libft_utils/ft_itoa.c\
		libft_utils/ft_strdup.c libft_utils/ft_str_alloc.c \
		libft_utils/ft_strtrim.c libft_utils/ft_substr.c libft_utils/ft_strjoin.c \
		libft_utils/ft_strchr.c libft_utils/ft_put.c libft_utils/ft_isalpha.c \
		libft_utils/ft_strcmp.c libft_utils/ft_free_list.c libft_utils/ft_split.c \
		libft_utils/ft_lstsize.c libft_utils/ft_lstlast.c libft_utils/ft_calloc.c\

RD_LINE2 = -L/goinfre/$(USER)/homebrew/opt/readline/lib

NAME = minishell
CC = cc
HEADER = minishell.h
FLAGS = -I./includes -I./libft -lreadline # -fsanitize=address -g #-Wall -Wextra -Werror 

all: $(NAME)
# -L ~/goinfre/homebrew/opt/readline/lib/
$(NAME): $(SRC) $(LIBFT)
	$(CC) $(FLAGS)   $(SRC) $(LIBFT) -lreadline -o $(NAME)
# -I ~/goinfre/homebrew/opt/readline/include/
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(NAME)
