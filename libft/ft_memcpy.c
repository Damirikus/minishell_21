#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	char	*rr;
	char	*oo;

	rr = (char *)destination;
	oo = (char *)source;
	if (!source && !destination)
		return (destination);
	while (n--)
		*rr++ = *oo++;
	return (destination);
}
