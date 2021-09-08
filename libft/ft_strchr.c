#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*str2;

	str2 = (char *)str;
	while (*str2 != '\0')
	{
		if (*str2 == ch)
			return (str2);
		str2++;
	}
	if (*str2 == ch)
		return (str2);
	return (NULL);
}
