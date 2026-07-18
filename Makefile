NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

SRC = src/main.c \
      src/parser.c \
      src/parser_check.c \
      src/parser_validate.c \
      src/error.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c codexion.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re