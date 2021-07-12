#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#define SIZE 1024

int		ft_strcmp(char *a, char *b);

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

int	ft_read_file(int file)
{
	int		size;
	char	buffer[SIZE];

	while (1)
	{
		size = read(file, buffer, SIZE);
		if (!size)
			break ;
		write(1, buffer, size);
	}
	return (0);
}

int	ft_read(char *program, char *arg)
{
	int	file;

	if (!ft_strcmp(arg, "-"))
		return (ft_read_file(0));
	file = open(arg, O_RDONLY);
	if (file == -1)
		return (ft_error(program, arg));
	return (ft_read_file(file));
}

int	main(int argc,	char **argv)
{
	int	index;
	int	error;

	if (argc < 2)
		return (ft_read_file(0));
	error = 0;
	index = 1;
	while (index < argc)
		error |= ft_read(argv[0], argv[index++]);
	return (error);
}
