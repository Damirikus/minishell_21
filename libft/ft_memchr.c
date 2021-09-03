#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	char	*rr;
	char	sym;
	size_t	i;

	rr = (char *)arr;
	sym = (char)c;
	i = 0;
	while (n--)
	{
		if (rr[i] == sym)
			return (&rr[i]);
		i++;
	}
	return (NULL);
}
