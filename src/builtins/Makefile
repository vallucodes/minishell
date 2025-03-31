NAME = test_builtins

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = test_builtins.c \
      ft_env.c \
      execute_builtins.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
