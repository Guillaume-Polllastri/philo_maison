# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 10:53:47 by gpollast          #+#    #+#              #
#    Updated: 2025/07/25 10:45:05 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = 	src/main.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I./includes -g

all: $(NAME)

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes ./$(NAME) $(ARGS) || true

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@echo "Suppression des fichiers objets (project)"

fclean: clean
	@rm -f $(NAME)
	@echo "Suppression de l'exécutable et des librairies"

re: fclean all

.PHONY: all val clean fclean re