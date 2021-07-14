#include "ft.h"

void	ft_copy(char *source, char *dest)
{
	int	i;

	i = 0 ;
	while (i < SIZE)
	{
		dest[i] = source[i];
		i++;
	}
}

int	ft_same(char *source, char *dest)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (source[i] != dest[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_fill(char *dest, int offset)
{
	int	i;

	i = offset;
	while (i < SIZE)
		dest[i++] = 0;
}

int	ft_init(t_data *data, int flag)
{
	data->count = 0;
	data->offset = 0;
	data->flag = flag;
	data->first = 1;
	data->same = 0;
	data->buffer = malloc(SIZE * sizeof(char));
	data->last = malloc(SIZE * sizeof(char));
	if (!data->buffer || !data->last)
		return (0);
	ft_fill(data->buffer, 0);
	ft_fill(data->last, 0);
	return (1);
}
