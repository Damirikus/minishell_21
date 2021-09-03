#include "libft.h"

void	*ft_calloc(size_t number, size_t size )
{
	char	*str;

	str = malloc(size * number);
	if (!str)
		return (NULL);
	ft_bzero(str, size * number);
	return ((void *)str);
}
