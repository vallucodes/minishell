NAME		= minishell.out
CC			= cc
CFLAGS		= -g -Wextra #-Wall -Werror
LDFLAGS		= -lreadline

LIBFT_DIR 	= ./lib/libft
LIBFT 		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj/
SRC_DIR		= src/

INCLUDES	= -I ./inc -I $(LIBFT_DIR)/inc

LIBFTH		= $(LIBFT_DIR)/inc/libft.h
MINISHH		= ./inc/minishell.h

SRC			=	main.c \
				print_development.c \
				init_minishell.c \
				memory_arena/memory_arena.c \
				ast.c \
				ast_branch_building.c \
				ast_dev.c \
				ast_utils.c \
				heredoc.c \
				heredoc_utils.c \
				tokenizer.c \
				tokenizer_utils.c \
				tokens_validation.c \
				retokenize_words.c \
				input_validation.c \
				error.c \
				environment/environment.c \
				environment/free_env.c \
				builtins/execute_builtins.c \
				builtins/ft_env.c \
				builtins/ft_pwd.c \
				builtins/ft_echo.c \
				builtins/ft_exit.c \
				builtins/ft_unset.c

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
