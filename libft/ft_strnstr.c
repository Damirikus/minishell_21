#include "libft.h"

char	*ft_need(char *bigs, char *littles, size_t lengths, size_t ks);

char	*ft_strnstr(const char *big, const char *little, size_t length)
{
	size_t	k;

	k = ft_strlen((char *)little);
	if (k == 0)
		return ((char *)big);
	if (length != 0)
		return (ft_need((char *)big, (char *)little, length, k));
	return (NULL);
}

char	*ft_need(char *bigs, char *littles, size_t lengths, size_t ks)
{
	size_t	temp;
	size_t	rr;
	size_t	i;

	i = 0;
	while ((char)bigs[i] != '\0' && i <= lengths - ks)
	{
		rr = 0;
		temp = 0;
		while ((char)bigs[i + temp] != '\0' && temp < ks)
		{
			if ((char)bigs[i + temp] == (char)littles[temp])
			{
				rr++;
				if (rr == ks)
					return ((char *)bigs + i);
			}
			temp++;
		}
		i++;
	}
	return (NULL);
}
