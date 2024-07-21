SRC = 	main.c \
		parsing/parsing.c \
		lexer/utils_lexer.c lexer/lexer.c lexer/token_type.c\
		builtin/cd.c builtin/init_env.c builtin/echo.c builtin/env.c builtin/export.c\

LIBFT = libft_utils/ft_lstadd_back.c libft_utils/ft_lstnew.c \
		libft_utils/ft_strlen.c libft_utils/ft_bzero.c \
		libft_utils/ft_strdup.c libft_utils/ft_str_alloc.c \
		libft_utils/ft_strtrim.c libft_utils/ft_substr.c  \
		libft_utils/ft_strchr.c libft_utils/ft_put.c \
		libft_utils/ft_strcmp.c libft_utils/ft_free_list.c\

NAME = minishell
CC = cc
FLAGS = -I./includes -I./libft -lreadline  #-Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(FLAGS)$(SRC) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(NAME)