#include <unistd.h>
#include <fcntl.h>

#define SIZE 1024

int	ft_error(char	*error)
{
	int	i;

	i = 0;
	while (error[i])
		i++;
	write(2, error, i);
	return (1);
}

int	main(int argc, char **argv)
{
	int		file;
	int		size;
	char	buffer[SIZE];

	if (argc < 2)
		return (ft_error("File name missing.\n"));
	if (argc > 2)
		return (ft_error("Too many arguments.\n"));
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		return (ft_error("Cannot read file.\n"));
	while (1)
	{
		size = read(file, buffer, SIZE);
		if (size)
			write(1, buffer, size);
		if (size < SIZE)
			break ;
	}
	return (0);
}
