

CC = cc

NAME = Philosopher

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SOURCES = main.c ft_atoi.c parser.c

OBJECT_FILE = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT_FILE)
	$(CC) $(CFLAGS) $(OBJECT_FILE) -o $(NAME)

%.o: %.c Philosopher.h
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	rm -f $(OBJECT_FILE)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
