# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/11 14:59:39 by ncruz-ne          #+#    #+#              #
#    Updated: 2026/01/12 12:58:39 by ncruz-ne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
HEADER = include/minitalk.h

LIBFT = libft/libft.a

SRC_DIR = src
OBJ_DIR = obj

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -D_DEFAULT_SOURCE

SERVER_SRC = $(SRC_DIR)/server.c
CLIENT_SRC = $(SRC_DIR)/client.c

SERVER_OBJ = $(OBJ_DIR)/server.o
CLIENT_OBJ = $(OBJ_DIR)/client.o


all: $(LIBFT) $(OBJ_DIR) $(SERVER) $(CLIENT)
	@echo "Server and Client are ready."

$(SERVER): $(LIBFT) $(SERVER_OBJ)
	@$(CC) $(CFLAGS) $(SERVER_OBJ) -Llibft -lft -o $@
	@echo "$@ compiled.\n"

$(CLIENT): $(LIBFT) $(CLIENT_OBJ)
	@$(CC) $(CFLAGS) $(CLIENT_OBJ) -Llibft -lft -o $@
	@echo "$@ compiled.\n"

$(LIBFT):
	@$(MAKE) -C libft libft.a
	@echo "$(LIBFT) compiled.\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(OBJ_DIR) directory created.\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ created.\n"


clean:
	@-rm -f $(SERVER_OBJ) $(CLIENT_OBJ)
	@-rm -rf $(OBJ_DIR)
	@$(MAKE) -C libft clean
	@echo "All object files and libraries removed.\n"

fclean: clean
	@-rm -f $(SERVER) $(CLIENT)
	@$(MAKE) -C libft fclean
	@echo "Executables, object files and libraries removed.\n"

re: fclean all

readme:
	@curl -sS -o README.md \
	https://raw.githubusercontent.com/neusamcn/minitalk/refs/heads/main/README.md
	@echo "\nREADME.md downloaded.\n"


.PHONY: all clean fclean re readme

