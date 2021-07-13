#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#define SIZE 16

typedef struct s_data
{
	char	*buffer;
	int		offset;
	int		count;
}	t_data;

void	ft_puterr(char *s);

void	ft_putchar(unsigned char c);

void	ft_puthex(unsigned int c, int padding);

void	ft_print_line(t_data *data, int size)
{
	int	i;

	ft_puthex(data->count, 7);
	write(1, "  ", 2);
	i = 0;
	while (i < 16)
	{
		if (i < size)
			ft_puthex(data->buffer[i], 1);
		else
			write(1, "  ", 2);
		write(1, " ", 1);
		if (i == 7)
			write(1, " ", 1);
		i++;
	}
	i = 0;
	write(1, " |", 2);
	while (i < 16 && i < size)
		ft_putchar(data->buffer[i++]);
	write(1, "|\n", 2);
}

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

int	ft_read_file(int file, t_data *data)
{
	int	size;

	while (1)
	{
		size = read(file, &((data->buffer)[data->offset]), SIZE - data->offset);
		if (!size)
			break ;
		data->offset += size;
		if (data->offset >= SIZE)
		{
			data->offset -= SIZE;
			ft_print_line(data, SIZE);
			data->count += SIZE;
		}
	}
	return (0);
}

int	ft_read(char *program, char *arg, t_data *data)
{
	int		file;

	file = open(arg, O_RDONLY);
	if (file == -1)
		return (ft_error(program, arg));
	return (ft_read_file(file, data));
}

int	main(int argc, char **argv)
{
	int		index;
	int		error;
	t_data	data;

	data.count = 0;
	data.offset = 0;
	data.buffer = malloc(SIZE * sizeof(char));
	if (argc < 3)
		ft_read_file(0, &data);
	index = 2;
	error = 0;
	while (index < argc)
		error |= ft_read(argv[0], argv[index++], &data);
	if (data.offset)
	{
		ft_print_line(&data, data.offset);
		data.count += data.offset;
	}
	if (data.count)
	{
		ft_puthex(data.count, 7);
		write(1, "\n", 1);
	}
	return (error);
}
