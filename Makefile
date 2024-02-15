C_NAME = client
S_NAME = server
LIBFT_A  = libft.a

C_SRC = client.c
S_SRC = server.c

C_OBJ = $(C_SRC:%.c=%.o)
S_OBJ = $(S_SRC:%.c=%.o)

HDR_DIR	  = ./server_client.h
HDR_LIB	  = ./libft/inc/
LIBFT_DIR = ./libft

CFLAGS = -Wall -Wextra -Werror

all: $(C_NAME) $(S_NAME)

$(S_NAME): $(S_OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(S_OBJ) $(LIBFT_DIR)/$(LIBFT_A) -o $@

$(C_NAME): $(C_OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(C_OBJ) $(LIBFT_DIR)/$(LIBFT_A) -o $@

%.o: %.c $(HDR_DIR)
	$(CC) $(CFLAGS) -I ./ -I $(HDR_LIB) -c -o $@ $<

$(LIBFT_A): FORCE
	$(MAKE) -C $(LIBFT_DIR)

FORCE :

clean:
	rm -rf *.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f server client
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re FORCE

FORCE:
