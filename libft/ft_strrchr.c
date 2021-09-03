#include "libft.h"

char	*ft_strrchr (const char *str, int ch)
{
	int		i;
	char	*str2;

	str2 = (char *)str;
	i = 0;
	while (str2[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str2[i] == ch)
			return (str2 + i);
		i--;
	}
	return (NULL);
}
