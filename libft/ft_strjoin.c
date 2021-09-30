#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	free((void *)s1);
	return (str);
}

char	*ft_strjoin_export(char *s1, char *s2)
{
	char	*dd;
	int		i;
	int		j;
	int		sl1;
	int		sl2;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	sl1 = ft_strlen_g(s1);
	sl2 = ft_strlen_g(s2);
	dd = (char *)malloc(sizeof(char) * (sl1 + sl2 + 1));
	if (dd == NULL)
		return (NULL);
	while (++i < sl1)
		dd[i] = s1[i];
	while (j < sl2)
		dd[i++] = s2[j++];
	dd[i] = '\0';
	free(s2);
	return (dd);
}
