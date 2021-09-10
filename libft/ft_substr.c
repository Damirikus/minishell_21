#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (start >= i)
		len = 0;
	if (len >= 0)
		ft_strlcpy(str, s + start, len + 1);
	return (str);
}
