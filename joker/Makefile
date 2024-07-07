SRC = srcs/parsing/parsing.c

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -I./includes

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) parcing.c $(SRC) -o $(NAME)

clean:
	rm -r $(NAME)