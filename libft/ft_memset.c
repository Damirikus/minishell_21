#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	void	*rr;

	rr = destination;
	i = 0;
	while (i < n)
	{
		*((char *)destination) = c;
		destination++;
		i++;
	}
	return (rr);
}
