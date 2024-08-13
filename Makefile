CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = -Llibft -lft
SRCS =  main.c \
		error/parsing_error.c \
		error/raise_cmd_error.c \
		error/raise_file_error.c \
		error/built_in_error.c \
		env/env.c \
		env/env_utils.c \
		env/find_env.c \
		env/get_envp.c \
		parser/parser_token.c \
		parser/parser_err_exception.c \
		parser/parser_init_free.c \
		parser/parser_utils.c \
		parser/command_path.c \
		parser/env_exception.c \
		parser/remove_block.c \
		parser/redirect_block.c \
		signal/ft_signal.c \
		tokenizer/tokenizer.c \
		tokenizer/token_utils.c \
		tokenizer/quote_token.c \
		tokenizer/interpreter.c \
		tokenizer/interpreter_utils.c \
		tokenizer/free_utils.c \
		command/command.c \
		command/heredoc.c \
		command/check_cmd_error.c \
		command/built_in/ft_cd.c \
		command/built_in/ft_pwd.c \
		command/built_in/ft_env.c \
		command/built_in/ft_echo.c \
		command/built_in/ft_exit.c \
		command/built_in/ft_unset.c \
		command/built_in/ft_export.c \
		command/built_in/ft_export_no_option.c \
		command/built_in/built_in.c \
		command/exec_redirection.c
#INCS = 	includes/minishell.h \
#		includes/built_in.h \
#		includes/exec.h \
#		includes/command.h \
#		includes/env.h \
#		includes/error.h \
#		includes/parser.h \
#		includes/ft_signal.h \
#		includes/tokenizer.h 
INCS =	./includes
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
NAME = minishell
COMPILE_FLAGS = -lreadline -L/opt/homebrew/opt/readline/lib
OBJ_FLAGS = -I/opt/homebrew/opt/readline/include

all : $(NAME)

$(NAME) : $(OBJECTS) $(INCS)
	make -C ./libft
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) $(OBJECTS) -I $(INCS) $(LIBFT) -o $(NAME) 
#$(CC) $(CFLAGS) -lreadline $(OBJECTS) $(LIBFT) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/command
	mkdir -p $(OBJ_DIR)/command/built_in
	mkdir -p $(OBJ_DIR)/env
	mkdir -p $(OBJ_DIR)/error
	mkdir -p $(OBJ_DIR)/tokenizer
	mkdir -p $(OBJ_DIR)/signal
	mkdir -p $(OBJ_DIR)/parser

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -I $(INCS) -c $< -o $@

clean :
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re :
	make fclean
	make all

debug : $(OBJECTS) $(INCS)
	make -C ./libft
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) -g -O0 -DDEBUG $(OBJECTS) $(LIBFT) -o $(NAME)_debug

.PHONY : all clean fclean re