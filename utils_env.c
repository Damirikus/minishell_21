#include "minishell.h"

char	*add_quotes(char *str)
{
	char	*result;
	int	i;
	int j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen_g(str) + 3));
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
