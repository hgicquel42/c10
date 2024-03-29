#include "ft.h"

void	ft_puterr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
}

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

void	ft_putchar(unsigned char c)
{
	if (c < 32 || c > 126)
		c = '.';
	write(1, &c, 1);
}

char	*g_hex = "0123456789abcdef";

void	ft_puthex(unsigned int n, int padding)
{
	char	c;

	if (n >= 16)
	{
		ft_puthex(n / 16, padding - 1);
		padding = 0;
	}
	while (padding > 0)
	{
		write(1, "0", 1);
		padding--;
	}
	c = g_hex[n % 16];
	write(1, &c, 1);
}
