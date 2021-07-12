NAME = ft_tail

FILES = \
	ft_tail.c \
	ft_utils.c

all: ${NAME}

${NAME}:
	gcc -Wall -Wextra -Werror -o ${NAME} ${FILES}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all