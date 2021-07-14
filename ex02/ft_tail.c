#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#define SIZE 16

char	*g_name;

int		ft_strcmp(char *a, char *b);

int		ft_atoi(char *s);

void	ft_putout(char *s);

void	ft_puterr(char *s);

void	ft_copy(char *source, char *dest, int size);

int	ft_error(char *file)
{
	ft_puterr(basename(g_name));
	ft_puterr(": ");
	ft_puterr(file);
	ft_puterr(": ");
	ft_puterr(strerror(errno));
	ft_puterr("\n");
	return (1);
}

int	ft_read_file(int file, int number)
{
	char	*previous;
	char	*current;
	int		offset;
	int		size;

	offset = 0;
	current = 0;
	while (1)
	{
		previous = current;
		current = malloc((offset + SIZE) * sizeof(char));
		if (!current)
			return (1);
		if (previous)
		{
			ft_copy(previous, current, offset);
			free(previous);
		}
		size = read(file, &current[offset], SIZE);
		if (!size)
			break ;
		offset += size;
	}
	write(1, &current[offset - number], number);
	return (0);
}

int	ft_read(char *arg, int number, int multiple, int last)
{
	int		file;

	file = open(arg, O_RDONLY);
	if (file == -1)
		return (ft_error(arg));
	if (multiple)
	{
		if (last)
			ft_putout("\n");
		ft_putout("==> ");
		ft_putout(arg);
		ft_putout(" <==\n");
	}
	return (ft_read_file(file, number));
}

int	main(int argc, char **argv)
{
	int	number;
	int	index;
	int	error;
	int	multiple;
	int	last;

	g_name = argv[0];
	if (argc < 2)
		return (1);
	index = 2;
	if (!ft_strcmp(argv[1], "-c"))
		number = ft_atoi(argv[index++]);
	else
		number = ft_atoi(&argv[index - 1][2]);
	error = 0;
	if (argc - index == 0)
		return (ft_read_file(0, number));
	multiple = argc - index > 1;
	while (index < argc)
	{
		last = multiple && argc - index == 1;
		error |= ft_read(argv[index], number, multiple, last);
		index++;
	}
	return (error);
}
