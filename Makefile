NAME		= minishell
CC			= cc
CFLAGS		= -g3 -Wextra #-Wall -Werror
LDFLAGS		= -lreadline

LIBFT_DIR 	= ./lib/libft
LIBFT 		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj/
SRC_DIR		= src/

INCLUDES	= -I ./inc -I $(LIBFT_DIR)/inc

LIBFTH		= $(LIBFT_DIR)/inc/libft.h
MINISHH		= ./inc/minishell.h

SRC			=	main.c \
				0.error_handling/error.c \
				0.init-delete/init_minishell.c \
				0.init-delete/delete_minishell.c \
				0.global_utils/utils.c \
				0.memory_arena/memory_arena.c \
				0.signals/signals.c \
				0.signals/signals_handlers.c \
				1.environment/environment.c \
				1.environment/free_env.c \
				2.input_validation/input_validation.c \
				3.tokens/create_tokens.c \
				3.tokens/init_lexer.c \
				3.tokens/retokenize_words_utils.c \
				3.tokens/retokenize_words.c \
				3.tokens/tokenizer_utils.c \
				3.tokens/tokenizer.c \
				3.tokens/tokens_validation.c \
				4.heredoc/heredoc.c \
				4.heredoc/heredoc_utils.c \
				4.heredoc/heredoc_cleanup.c \
				5.quotes_handle/quotes_handler.c \
				5.quotes_handle/quotes_handler_utils.c \
				5.quotes_handle/quotes_handler_utils2.c \
				6.expansion/expansion.c \
				7.ast/ast.c \
				7.ast/ast_branch_building.c \
				7.ast/ast_dev.c \
				7.ast/ast_utils.c \
				20.builtins/ft_env.c \
				20.builtins/ft_pwd.c \
				20.builtins/ft_cd.c \
				20.builtins/ft_echo.c \
				20.builtins/ft_exit.c \
				20.builtins/ft_unset.c \
				20.builtins/ft_export.c \
				20.builtins/utils_builtins.c \
				20.builtins/ft_export_sort_env.c \
				99.dev/print_development.c \
				execution/safe_open.c \
				execution/execute_builtin.c \
				execution/path.c \
				execution/setup_child_fds.c \
				execution/execution.c \
				execution/wait.c


OBJS		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MINISHH) $(LIBFTH)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(LIBFT) $(OBJS) $(MINISHH) $(LIBFTH)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "\033[0;32mMinishell built successfully ✅\033[0m"


clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "\033[0;32mMinishell cleaned successfully ✅\033[0m"


fclean: clean
	@rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re
