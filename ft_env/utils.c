#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*ss1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	if (!(ss1 = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (s1[j] != '\0')
	{
		ss1[j] = s1[j];
		j++;
	}
	ss1[j] = '\0';
	return (ss1);
}

int	ft_strlen_g(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*add_quotes(char *str)
{
	char	*result;
	int	i;
	int j;
	
	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen_g(str) + 2));
	while (str[i] != '\0' && str[i] != '=')
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j++] = str[i++];
	result[j++] = '"';
	while (str[i] != '\0')
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j++] = '"';
	result[j] = '\0';
	return (result);
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
