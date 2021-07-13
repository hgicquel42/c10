#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#define SIZE 1024

int		ft_strcmp(char *a, char *b);

int		ft_atoi(char *s);

void	ft_putout(char *s);

void	ft_puterr(char *s);

int	ft_error(char *program, char *file)
{
	ft_puterr(basename(program));
	ft_puterr(": ");
	ft_puterr(file);
	ft_puterr(": ");
	ft_puterr(strerror(errno));
	ft_puterr("\n");
	return (1);
}

void	ft_name(char *arg)
{
	ft_putout("==> ");
	ft_putout(arg);
	ft_putout(" <==\n");
}

int	ft_read_file(int file, int number)
{
	char	*buffer;
	int		offset;
	int		count;

	offset = 0;
	buffer = malloc(SIZE * sizeof(char));
	while (read(file, &buffer[offset], 1))
	{
		if (offset >= SIZE - 1)
			offset -= SIZE;
		offset++;
	}
	if (number <= offset)
		write(1, &buffer[offset - number], number);
	else
	{
		count = number - offset - 1;
		write(1, &buffer[SIZE - 1 - (count)], count);
		write(1, &buffer[0], offset);
	}
	return (0);
}

int	ft_read(char *program, char *arg, int number)
{
	int		file;

	file = open(arg, O_RDONLY);
	if (file == -1)
		return (ft_error(program, arg));
	return (ft_read_file(file, number));
}

int	main(int argc, char **argv)
{
	int	number;
	int	index;
	int	error;
	int	count;

	if (argc < 2)
		return (1);
	index = 2;
	if (!ft_strcmp(argv[1], "-c"))
		number = ft_atoi(argv[index++]);
	else
		number = ft_atoi(&argv[index - 1][2]);
	error = 0;
	count = argc - index;
	if (!count)
		return (ft_read_file(0, number));
	while (index < argc)
	{
		if (count > 1 && index == argc - 1)
			ft_putout("\n");
		if (count > 1)
			ft_name(argv[index]);
		error |= ft_read(argv[0], argv[index++], number);
	}
	return (error);
}
