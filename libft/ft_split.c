#include "libft.h"

int	ft_slova(char *str, char sym);
int	ft_bukvy(char **mas, char *st, char symb, int i);

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**arr;
	int		n;

	if (!s)
		return (NULL);
	n = ft_slova((char *)s, c);
	arr = malloc((n + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[n] = 0;
	j = 0;
	while (j < n)
	{
		s += ft_bukvy(&arr[j], (char *)s, c, 0);
		if ((int)s == -1)
			return (NULL);
		j++;
	}
	return (arr);
}

int	ft_bukvy(char **mas, char *st, char symb, int i)
{
	int	count;

	count = 0;
	while (st[i] != '\0')
	{
		if (st[i] != symb)
		{
			while (st[i] != symb && st[i] != '\0')
			{
				i++;
				count++;
			}
			break ;
		}
		i++;
	}
	*mas = (char *)malloc(count + 1);
	if (!*mas)
		return (-1);
	ft_strlcpy(*mas, st + (i - count), count + 1);
	return (i);
}

int	ft_slova(char *str, char sym)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sym)
		{
			while (str[i] != sym && str[i + 1] != '\0')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}
