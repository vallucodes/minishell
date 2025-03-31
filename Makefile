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
				ast.c \
				ast_branch_building.c \
				ast_dev.c \
				ast_utils.c \
				heredoc.c \
				tokenizer.c \
				tokenizer_utils.c \
				tokens_validation.c \
				retokenize_words.c \
				input_validation.c \
				error.c \
				environment/environment.c \
				environment/free_env.c

OBJS		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(MINISHH) $(LIBFTH)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(LIBFT) $(OBJS) $(MINISHH) $(LIBFTH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all, clean, fclean, re
