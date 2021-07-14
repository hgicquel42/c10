#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

//REMOVE
#include <stdio.h>

#define SIZE 16

typedef struct s_data
{
	char	*last;
	char	*buffer;
	int		first;
	int		same;
	int		offset;
	int		count;
}	t_data;

void	ft_puterr(char *s);

void	ft_putchar(unsigned char c);

void	ft_puthex(unsigned int c, int padding);

void	ft_bufcopy(char	*source, char *dest)
{
	int	i;

	i = 0 ;
	while (i < SIZE)
	{
		dest[i] = source[i];
		i++;
	}
}

int	ft_same(t_data *data, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (data->buffer[i] != data->last[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_print(t_data *data, int size)
{
	int	i;

	ft_puthex(data->count, 7);
	write(1, "  ", 2);
	i = 0;
	while (i < 16)
	{
		if (i < size)
			ft_puthex((unsigned int) (unsigned char) data->buffer[i], 1);
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

void	ft_flush(t_data *data, int size)
{
	if (data->first || !ft_same(data, size))
	{
		data->first = 0;
		data->same = 0;
		ft_print(data, size);
		ft_bufcopy(data->buffer, data->last);
	}
	else
	{
		if (!data->same)
			write(1, "*\n", 2);	
		data->same = 1;
	}
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
			ft_flush(data, SIZE);
			data->count += SIZE;
		}
	}
	return (0);
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

int	ft_read(int argc, char **argv, int index, t_data *data)
{
	int		file;

	file = open(argv[index], O_RDONLY);
	if (file == -1)
	{
		ft_error(argv[0], argv[index]);
		if (index == argc - 1 && data->first)
		{
			if (read(file, data->buffer, 1) == -1)
				ft_error(argv[0], argv[index]);
		}
		return (1);
	}
	return (ft_read_file(file, data));
}

int	ft_init(t_data *data)
{
	int i;

	data->count = 0;
	data->offset = 0;
	data->first = 1;
	data->same = 0;
	data->buffer = malloc(SIZE * sizeof(char));
	data->last = malloc(SIZE * sizeof(char));
	if (!data->buffer || !data->last)
		return (0);
	i = 0;
	while (i < SIZE)
		data->last[i++] = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	int		index;
	int		error;
	t_data	data;

	if (!ft_init(&data))
		return (1);
	if (argc < 3)
		ft_read_file(0, &data);
	index = 2;
	error = 0;
	while (index < argc)
		error |= ft_read(argc, argv, index++, &data);
	if (data.offset)
	{
		ft_flush(&data, data.offset);
		data.count += data.offset;
	}
	if (data.count)
	{
		ft_puthex(data.count, 7);
		write(1, "\n", 1);
	}
	return (error);
}
