#ifndef FT_H
# define FT_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <libgen.h>
# define SIZE 16

typedef struct s_data
{
	char	*last;
	char	*buffer;
	int		first;
	int		same;
	int		offset;
	int		count;
	int		flag;
}	t_data;

int		ft_strcmp(char *a, char *b);

int		ft_error(char *program, char *file);

void	ft_putchar(unsigned char c);

void	ft_puthex(unsigned int c, int padding);

void	ft_copy(char *source, char *dest);

int		ft_same(char *source, char *dest);

void	ft_fill(char *dest, int offset);

int		ft_init(t_data *data, int flag);

void	ft_print_next(t_data *data);

void	ft_print_flag(t_data *data, int size);

void	ft_print_normal(t_data *data, int size);

#endif