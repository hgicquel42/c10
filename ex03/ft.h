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
}	t_data;

#endif