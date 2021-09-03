#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*str;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
		str[len] = f(len, s[len]);
	return (str);
}
