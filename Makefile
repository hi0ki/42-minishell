SRC = srcs/parsing/parsing.c

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -I./includes

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) srcs/main.c $(SRC) -o $(NAME)

clean:
	rm -r $(NAME)