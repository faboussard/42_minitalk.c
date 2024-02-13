SERVER = server
CLIENT = client

CFLAGS = -Wall -Werror -Wextra
CC = cc
FLAGS = -Wall -Wextra -Werror -Ilibft/inc -Llibft -lft

LIBFT = libft

DIR_OBJS = libft/.objs/

# Liste des fichiers source pour server et client
SERVER_SRC = server.c
CLIENT_SRC = client.c

# Liste des fichiers header dont dépendent les fichiers source
DEPS = libft.h server_client.h

all: $(SERVER) $(CLIENT)

# Règle de compilation pour le serveur
$(SERVER): $(SERVER_SRC:.c=.o) $(LIBFT)
	@$(CC) $(CFLAGS) $(FLAGS) -o $(SERVER) $(SERVER_SRC:.c=.o)

# Règle de compilation pour le client
$(CLIENT): $(CLIENT_SRC:.c=.o) $(LIBFT)
	@$(CC) $(CFLAGS) $(FLAGS) -o $(CLIENT) $(CLIENT_SRC:.c=.o)

# Règle de compilation des fichiers source
%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@ -Ilibft/inc

# Construction de la librairie libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT)

clean:
	@$(MAKE) clean -C $(LIBFT)
	@rm -rf $(DIR_OBJS) $(SERVER_SRC:.c=.o) $(CLIENT_SRC:.c=.o)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT)
	@rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re



