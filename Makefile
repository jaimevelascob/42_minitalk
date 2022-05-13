CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all: server client

SERVER_SRC := src/server.c utils/ft_putstr.c utils/ft_strcat.c utils/ft_strlen.c utils/ft_calloc.c
SERVER_OBJ := $(SERVER_SRC:.c=.o)
CLIENT_SRC := src/client.c utils/ft_putstr.c utils/ft_atoi.c utils/ft_strlen.c utils/ft_putnbr_fd.c 
CLIENT_OBJ := $(CLIENT_SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

server: $(SERVER_OBJ)
	@echo "compiling..."
	@gcc $(CFLAGS) -o server $(SERVER_OBJ)
client: $(CLIENT_OBJ)
	@gcc $(CFLAGS) -o client $(CLIENT_OBJ)
clean:
	@echo "cleaning..."
	@rm -f server client
fclean: clean
	@rm -f $(SERVER_OBJ) $(CLIENT_OBJ) 

re: fclean all

.PHONY: clean fclean re default
