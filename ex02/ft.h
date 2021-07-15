#ifndef FT_H
# define FT_H
# include <errno.h>
# include <string.h>
# include <libgen.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*g_name;

int		ft_strcmp(char *a, char *b);

int		ft_atoi(char *s);

void	ft_putout(char *s);

void	ft_puterr(char *s);

int		ft_error(char *file);

void	ft_copy(char *source, char *dest, int size);

#endif