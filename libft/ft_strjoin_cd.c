#include "libft.h"

char	*ft_strjoin_cd(char const *s1, char const *s2)
{
	int		ls1;
	int		ls2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen((char *)s1);
	ls2 = ft_strlen((char *)s2);
	str = (char *)malloc(ls1 + ls2 + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ls1 + 1);
	ft_strlcpy(str + ls1, s2, ls2 + 1);
	return (str);
}
