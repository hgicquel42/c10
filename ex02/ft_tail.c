#include "ft.h"

#define SIZE 1024

char	*ft_alloc(char *old, int offset)
{
	char	*new;
	int		i;

	new = malloc((offset + SIZE) * sizeof(char));
	if (!new)
		return (0);
	i = 0;
	while (i < (offset + SIZE))
	{
		if (i < offset)
			new[i] = old[i];
		else
			new[i] = 0;
		i++;
	}
	if (old)
		free(old);
	return (new);
}

int	ft_read_file(int file, int number)
{
	char	*buffer;
	int		offset;
	int		size;

	offset = 0;
	buffer = 0;
	while (1)
	{
		buffer = ft_alloc(buffer, offset);
		if (!buffer)
			return (1);
		size = read(file, &buffer[offset], SIZE);
		if (!size)
			break ;
		offset += size;
	}
	if (offset >= number)
		write(1, &buffer[offset - number], number);
	else
		write(1, &buffer[0], offset);
	return (0);
}

int	ft_read(char *arg, int number, int multiple, int *first)
{
	int		file;

	file = open(arg, O_RDONLY);
	if (file == -1)
		return (ft_error(arg));
	if (multiple)
	{
		if (!*first)
			ft_putout("\n");
		ft_putout("==> ");
		ft_putout(arg);
		ft_putout(" <==\n");
		*first = 0;
	}
	return (ft_read_file(file, number));
}

int	main(int argc, char **argv)
{
	int	number;
	int	index;
	int	error;
	int	multiple;
	int	first;

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
	first = 1;
	while (index < argc)
	{
		error |= ft_read(argv[index], number, multiple, &first);
		index++;
	}
	return (error);
}
