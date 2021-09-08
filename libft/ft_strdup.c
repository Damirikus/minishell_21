#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*str;
	int		k;

	k = ft_strlen(src);
	str = (char *)malloc(sizeof(*str) * (k + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (src[k] != '\0')
	{
		str[k] = src[k];
		k++;
	}
	str[k] = '\0';
	return (str);
}
