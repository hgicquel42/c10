#include <unistd.h>

int	ft_strcmp(char *a, char *b)
{
	while (*a && *a == *b)
		a++, b++;
	return (*a - *b);
}

void	ft_puterr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
}
