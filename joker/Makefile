SRC = srcs/parsing/parsing.c srcs/main.c
LIBFT = libft_utils/ft_lstadd_back.c libft_utils/ft_lstnew.c libft_utils/ft_strlen.c libft_utils/ft_bzero.c

NAME = minishell
CC = cc
FLAGS = -I./includes -I./libft -lreadline  #-Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(FLAGS)$(SRC) $(LIBFT) -o $(NAME)

clean:
	rm -r $(NAME)