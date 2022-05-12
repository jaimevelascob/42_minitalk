CFLAGS = -Wall -Wextra -Werror

normi = norminette -R CheckForbiddenSourceHeader

all: server client

server: 
	gcc $(CFLAGS) server.c -o server
client: 
	gcc $(CFLAGS) client.c utils/ft_atoi.c utils/ft_strlen.c -o client
clean:
	-rm -f server.o client.o
fclean: clean
	-rm -f server client

re: fclean all

.PHONY: clean fclean re default
