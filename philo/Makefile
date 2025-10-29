# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 10:53:47 by gpollast          #+#    #+#              #
#    Updated: 2025/10/29 14:28:08 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = 	src/main.c \
		src/parse.c \
		src/data_init.c \
		src/utils.c \
		src/philos.c \
		src/fork.c \
		src/atomic.c \
		src/atomic_2.c \
		src/the_reaper.c \
		src/the_order.c \
		src/utils2.c

OBJ_DIR = obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -I./includes -g

all: $(NAME)

val:
	valgrind --trace-children=yes --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all ./$(NAME) $(ARGS) || true

# Helgrind pour détecter les deadlocks
helgrind:
	valgrind --tool=helgrind --track-lockorders=yes --history-level=full --conflict-cache-size=1000000 ./$(NAME) $(ARGS)

# Helgrind avec plus de détails sur les deadlocks
helgrind-verbose:
	valgrind --tool=helgrind --fair-sched=yes --track-lockorders=yes --history-level=full --conflict-cache-size=1000000 --show-below-main=yes -v ./$(NAME) $(ARGS)

# DRD alternative pour comparaison
drd:
	valgrind --tool=drd --check-stack-var=yes --exclusive-threshold=500 ./$(NAME) $(ARGS)

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

.PHONY: all val helgrind helgrind-verbose drd clean fclean re