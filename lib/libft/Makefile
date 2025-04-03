NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
SRC_DIR	= src/
OBJ_DIR	= obj/

HEADERS	= -I ./inc

SRC	= \
			ft_atoi_base.c \
			ft_atoi.c \
			ft_atol.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_is_numeric.c \
			ft_is_all_whitespace.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_maxf.c \
			ft_maxi.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_minf.c \
			ft_mini.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_free_2d.c \
			dprintf/printf.c \
 			dprintf/printf_types.c \
			dprintf/printf_types2.c \
			dprintf/printf_utils.c

OBJS	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $@ $?
	@echo "\033[0;32mLibft created successfully ✅\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $< -o $@ $(HEADERS)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;32mLibft cleaned successfully ✅\033[0m"


fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
