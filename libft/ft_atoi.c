#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	k;

	k = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			k = -1;
		else
			k = 1;
		i++;
	}
	nb = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = 10 * nb + (str[i] - 48);
		i++;
	}
	return (nb * k);
}
