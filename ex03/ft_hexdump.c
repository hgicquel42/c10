#include "ft.h"

void	ft_flush(t_data *data, int size)
{
	if (size < SIZE)
		ft_fill(data->buffer, size);
	if (data->first || !ft_same(data->buffer, data->last))
	{
		data->first = 0;
		data->same = 0;
		if (data->flag)
			ft_print_flag(data, size);
		else
			ft_print_normal(data, size);
		ft_copy(data->buffer, data->last);
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

int	main(int argc, char **argv)
{
	int		index;
	int		error;
	t_data	data;

	index = 1;
	if (argc > 1 && !ft_strcmp(argv[1], "-C"))
		index++;
	if (!ft_init(&data, index == 2))
		return (1);
	if (index == argc)
		ft_read_file(0, &data);
	error = 0;
	while (index < argc)
		error |= ft_read(argc, argv, index++, &data);
	if (data.offset)
	{
		ft_flush(&data, data.offset);
		data.count += data.offset;
	}
	if (data.count)
		ft_print_next(&data);
	return (error);
}
