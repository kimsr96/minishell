CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = -Llibft -lft
SRCS =  main.c \
		tokenizer/tokenizer.c \
		tokenizer/command_token.c \
		tokenizer/token_utils.c \
		tokenizer/quote_token.c \
		tokenizer/quote_token_utils.c \
		tokenizer/env_token.c \
		built_in/cd.c \
		built_in/pwd.c \
		built_in/echo.c \
		parser/parser_token.c \
		parser/parser_free.c \
		parser/parser_utils.c 
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC = minishell.h
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJECTS) $(INC)
	make -C ./libft
	$(CC) $(CFLAGS) -lreadline $(OBJECTS) $(LIBFT) -o $(NAME) 

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/tokenizer
	mkdir -p $(OBJ_DIR)/built_in
	mkdir -p $(OBJ_DIR)/parser

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re