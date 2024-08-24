SRC = 	main.c\
		../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c \
		parsing/parsing.c parsing/fill_variables.c parsing/join_data.c parsing/create_lst.c parsing/parsing_utils.c parsing/parsing_type.c \
		parsing/fill_files.c parsing/fill_array.c parsing/fill_path.c parsing/heredoc.c parsing/utils_variables.c parsing/heredoc_utils.c\
		lexer/utils_lexer.c lexer/lexer.c lexer/token_type.c lexer/error_handler.c  lexer/check_operators.c\
		builtin/cd.c builtin/init_env.c builtin/echo.c builtin/env.c builtin/export.c builtin/pwd.c builtin/unset.c builtin/exit.c \
		exec/exec.c exec/link_builtin.c exec/exec_utils.c builtin/builtin_utils.c \

LIBFT = libft_utils/ft_lstadd_back.c libft_utils/ft_lstnew.c \
		libft_utils/ft_strlen.c libft_utils/ft_bzero.c libft_utils/ft_itoa.c\
		libft_utils/ft_strdup.c libft_utils/ft_str_alloc.c \
		libft_utils/ft_strtrim.c libft_utils/ft_substr.c libft_utils/ft_strjoin.c \
		libft_utils/ft_strchr.c libft_utils/ft_put.c libft_utils/ft_isalpha.c \
		libft_utils/ft_strcmp.c libft_utils/ft_free_list.c libft_utils/ft_split.c \
		libft_utils/ft_lstsize.c libft_utils/ft_lstlast.c libft_utils/ft_calloc.c\

NAME = minishell
CC = cc
FLAGS =  -Wall -Wextra -Werror -I./libft -lreadline
HEADER = includes/minishell.h

OBJS = $(SRC:.c=.o)
LIBOBJ = $(LIBFT:.c=.o)

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m 

all: $(NAME)

$(NAME): $(OBJS) $(LIBOBJ)
	@$(CC) $(FLAGS) -L ~/goinfre/homebrew/opt/readline/lib/ $(OBJS) $(LIBOBJ) -o $(NAME)

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -I ~/goinfre/homebrew/opt/readline/include/  -c $< -o $@

clean:
	@echo "${RED}Cleaning objects...${NC}"
	@rm -rf $(OBJS) $(LIBOBJ)
	@echo "${GREEN}Objects cleaned${NC}"

fclean: clean
	@echo "${RED}Cleaning executable...${NC}"
	@rm -rf $(NAME)
	@echo "${GREEN}Executable cleaned${NC}"

re: fclean all
