CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = -Llibft -lft
SRCS =  srcs/main.c \
		srcs/error/raise_heredoc_error.c \
		srcs/error/raise_parsing_error.c \
		srcs/error/raise_cmd_error.c \
		srcs/error/raise_file_error.c \
		srcs/error/raise_built_in_error.c \
		srcs/env/env.c \
		srcs/env/env_utils.c \
		srcs/env/find_env.c \
		srcs/env/get_envp.c \
		srcs/parser/parser_token.c \
		srcs/parser/parser_err_exception.c \
		srcs/parser/parser_init_free.c \
		srcs/parser/parser_utils.c \
		srcs/parser/command_path.c \
		srcs/parser/redirect_block.c \
		srcs/signal/ft_signal.c \
		srcs/tokenizer/tokenizer.c \
		srcs/tokenizer/token_utils.c \
		srcs/tokenizer/quote_token.c \
		srcs/tokenizer/heredoc_interpreter.c \
		srcs/tokenizer/interpreter.c \
		srcs/tokenizer/interpreter_utils.c \
		srcs/tokenizer/free_utils.c \
		srcs/exec/heredoc.c \
		srcs/exec/heredoc_env.c \
		srcs/exec/heredoc_utils.c \
		srcs/exec/check_cmd_error.c \
		srcs/exec/built_in/ft_cd.c \
		srcs/exec/built_in/ft_pwd.c \
		srcs/exec/built_in/ft_env.c \
		srcs/exec/built_in/ft_echo.c \
		srcs/exec/built_in/ft_exit.c \
		srcs/exec/built_in/ft_unset.c \
		srcs/exec/built_in/ft_export.c \
		srcs/exec/built_in/ft_export_no_option.c \
		srcs/exec/built_in/built_in.c \
		srcs/exec/exec_redirection.c \
		srcs/exec/exec_utils.c \
		srcs/exec/exec1.c \
		srcs/exec/exec2.c \
		srcs/exec/wait.c
INCS =	./includes
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJECTS) $(INCS)
	make -C ./libft
	$(CC) $(CFLAGS) -lreadline $(OBJECTS) -I $(INCS) $(LIBFT) -o $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/srcs
	mkdir -p $(OBJ_DIR)/srcs/exec
	mkdir -p $(OBJ_DIR)/srcs/exec/built_in
	mkdir -p $(OBJ_DIR)/srcs/env
	mkdir -p $(OBJ_DIR)/srcs/error
	mkdir -p $(OBJ_DIR)/srcs/tokenizer
	mkdir -p $(OBJ_DIR)/srcs/signal
	mkdir -p $(OBJ_DIR)/srcs/parser

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

.PHONY : all clean fclean re