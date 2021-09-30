#include "libft.h"

void	ft_bzero1(int *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*s = 0;
		s++;
		i++;
	}
}
