#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	char	*dd;
	char	*ss;
	size_t	i;

	i = n;
	dd = (char *)destination;
	ss = (char *)source;
	if (!source && !destination)
		return (destination);
	if (source < destination)
		while (i--)
			dd[i] = ss[i];
	if (source > destination)
		while (n--)
			*dd++ = *ss++;
	return (destination);
}
