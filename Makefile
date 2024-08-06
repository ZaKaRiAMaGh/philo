# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zmaghdao <zmaghdao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 09:48:29 by zmaghdao          #+#    #+#              #
#    Updated: 2024/08/06 09:48:29 by zmaghdao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = Philosopher

CFLAGS = #-Wall -Wextra -Werror #-pthread #-g #-fsanitize=address 

SOURCES = main.c ft_atoi.c parser.c

OBJECT_FILE = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT_FILE)
	$(CC) $(CFLAGS) $(OBJECT_FILE) -o $(NAME)

%.o: %.c Philosopher.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT_FILE)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
