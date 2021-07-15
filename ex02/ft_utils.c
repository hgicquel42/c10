#include "ft.h"

int	ft_strcmp(char *a, char *b)
{
	while (*a && *a == *b)
		a++, b++;
	return (*a - *b);
}

int	ft_atoi(char *s)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (s[i])
		n = (n * 10) + (s[i++] - '0');
	return (n);
}

void	ft_putout(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void	ft_puterr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
}

int	ft_error(char *file)
{
	ft_puterr(basename(g_name));
	ft_puterr(": ");
	ft_puterr(file);
	ft_puterr(": ");
	ft_puterr(strerror(errno));
	ft_puterr("\n");
	return (1);
}
