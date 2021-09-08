#include "libft.h"

void	*ft_memccpy (void *destination, const void *source, int c, size_t n)
{
	char	*dd;
	char	*ss;
	char	sym;

	sym = (char)c;
	dd = (char *)destination;
	ss = (char *)source;
	if (!source && !destination)
		return (destination);
	while (n--)
	{
		*dd = *ss;
		if (*ss == sym)
			return ((void *)dd + 1);
		dd++;
		ss++;
	}
	return (NULL);
}
