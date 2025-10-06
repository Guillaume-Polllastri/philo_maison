# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 10:53:47 by gpollast          #+#    #+#              #
#    Updated: 2025/10/06 15:04:55 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = 	src/main.c \
		src/parse.c \
		src/init.c \
		src/utils.c \
		src/exec.

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -I./includes -g

all: $(NAME)

val:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes ./$(NAME) $(ARGS) || true

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Suppression des fichiers objets (project)"

fclean: clean
	@rm -f $(NAME)
	@echo "Suppression de l'exécutable et des librairies"

re: fclean all

.PHONY: all val clean fclean re