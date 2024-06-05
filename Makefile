CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = -Llibft -lft
SRCS = tokenizer/tokenizer.c tokenizer/token_utils.c \
		tokenizer/quote_parser.c tokenizer/quote_parser_utils.c \
		tokenizer/env_parser.c \
		built_in/cd.c built_in/pwd.c built_in/echo.c \
 		main.c command.c
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
	mkdir -p $(OBJ_DIR)/parser
	mkdir -p $(OBJ_DIR)/built_in

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