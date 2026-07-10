NAME = tests_runner
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = tests.c ../get_next_line.c ../get_next_line_utils.c
OBJ = $(SRC:.c=.o)
ADD = -D BUFFER_SIZE=2

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(ADD) $(OBJ) -o $(NAME)

%.o: %.c ../get_next_line.h
	$(CC) $(CFLAGS) $(ADD) -c $< -o $@

test: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all test clean fclean re