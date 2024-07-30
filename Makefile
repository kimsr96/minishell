CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LIBFT = -Llibft -lft
SRCS =  main.c \
		command/command.c \
		command/built_in/ft_cd.c \
		command/built_in/ft_pwd.c \
		command/built_in/ft_env.c \
		command/built_in/ft_echo.c \
		command/built_in/ft_exit.c \
		command/built_in/ft_unset.c \
		command/built_in/ft_export.c \
		command/built_in/ft_exit_status.c \
		command/built_in/ft_export_no_option.c \
		command/built_in/built_in.c \
		command/exec/exec_redirection.c \
		env/env.c \
		env/env_utils.c \
		env/find_env.c \
		env/get_envp.c \
		error/error.c \
		parser/parser_token.c \
		parser/parser_init_free.c \
		parser/parser_utils.c \
		parser/command_path.c \
		parser/env_exception.c \
		parser/pipe_exception.c \
		parser/remove_block.c \
		parser/redirect_block.c \
		signal/ft_signal.c \
		tokenizer/tokenizer.c \
		tokenizer/token_utils.c \
		tokenizer/quote_token.c \
		tokenizer/quote_token_utils.c \
		tokenizer/env_token.c

OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC = minishell.h
NAME = minishell
COMPILE_FLAGS = -lreadline -L/opt/homebrew/opt/readline/lib
OBJ_FLAGS = -I/opt/homebrew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJECTS) $(INC)
	make -C ./libft
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)
#$(CC) $(CFLAGS) -lreadline $(OBJECTS) $(LIBFT) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/command
	mkdir -p $(OBJ_DIR)/command/exec
	mkdir -p $(OBJ_DIR)/command/built_in
	mkdir -p $(OBJ_DIR)/env
	mkdir -p $(OBJ_DIR)/error
	mkdir -p $(OBJ_DIR)/tokenizer
	mkdir -p $(OBJ_DIR)/signal
	mkdir -p $(OBJ_DIR)/parser

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean :
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re :
	make fclean
	make all

debug : $(OBJECTS) $(INC)
	make -C ./libft
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) -g -O0 -DDEBUG $(OBJECTS) $(LIBFT) -o $(NAME)_debug

.PHONY : all clean fclean re