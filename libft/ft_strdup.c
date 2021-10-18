#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*ss1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	ss1 = (char *)malloc(sizeof(char) * (i + 1));
	if (ss1 == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		ss1[j] = s1[j];
		j++;
	}
	ss1[j] = '\0';
	return (ss1);
}
