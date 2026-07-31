NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -pthread

SRC = src/main.c \
      src/parser.c \
      src/parser_check.c \
      src/parser_validate.c \
      src/error.c \
      src/init_dongles.c \
      src/init_coders.c \
      src/init_program.c \
      src/destroy.c \
      src/time.c \
      src/time_utils.c \
      src/logger.c \
      src/coder.c \
      src/coder_dongles.c \
      src/threads.c \
      src/state.c \
      src/monitor.c

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