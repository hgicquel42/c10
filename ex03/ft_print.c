#include "ft.h"

void	ft_print_next(t_data *data)
{
	if (data->flag)
		ft_puthex(data->count, 7);
	else
		ft_puthex(data->count, 6);
	write(1, "\n", 1);
}

void	ft_print_flag(t_data *data, int size)
{
	int	i;

	ft_puthex(data->count, 7);
	write(1, "  ", 2);
	i = 0;
	while (i < 16)
	{
		if (i < size)
			ft_puthex((unsigned int)(unsigned char) data->buffer[i], 1);
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

void	ft_print_normal(t_data *data, int size)
{
	int	i;

	ft_puthex(data->count, 6);
	write(1, " ", 2);
	i = 0;
	while (i < 16)
	{
		if (i < size)
			ft_puthex((unsigned int)(unsigned char) data->buffer[i], 1);
		else
			write(1, "  ", 2);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
