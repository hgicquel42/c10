NAME = ft_hexdump

FILES = \
	ft_hexdump.c \
	ft_utils.c

all: ${NAME}

${NAME}:
	gcc -Wall -Wextra -Werror -o ${NAME} ${FILES}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all