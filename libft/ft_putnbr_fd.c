#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		r;
	int long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = nb * (-1);
		write(fd, "-", 1);
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	r = nb % 10 + 48;
	write(fd, &r, 1);
}
