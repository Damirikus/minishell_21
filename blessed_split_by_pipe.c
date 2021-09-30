#include "minishell.h"

void	ft_skip_quotes(char *str, int *i) // Просто пропускаем кавычки
{
	*i = *i + 1;
	if (str[*i - 1] == '\"')
	{
		while (str[*i] != '\"' && str[*i] != '\0')
			*i = *i  + 1;
		*i = *i  + 1;
		return ;
	}
	else if (str[*i - 1] == '\'')
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i  + 1;
		*i = *i  + 1;
		return ;
	}
}

int	how_much_pipes(char *str)
{
	int	i;
	int	pipes;
	
	i = 0;
	pipes = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			ft_skip_quotes(str, &i);
		if (str[i] == '|')
			pipes++;
		if (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
			i++;
	}
	return (pipes);
}

int	*take_coordinates(char *str) // ищем координаты пайпов /////// char *str = "ls '\"-la\"' '|' < \"<>  < > \"5";
{
	int	i;
	int	j;
	int	pipes;
	int	*coordinates;
	
	i = 0;
	j = 0;
	pipes = how_much_pipes(str);
	coordinates = malloc(sizeof(int) * (pipes + 1));
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			ft_skip_quotes(str, &i);
		if (str[i] == '|')
		{
			coordinates[j] = i;
			j++;
		}
		if (str[i] != '\"' && str[i] != '\'' && str[i] != '\0')
			i++;
	}
	coordinates[j] = -1;
	return (coordinates);
}

char	*ft_cutstr(char *str, int start, int finish)
{
	int		len;
	int		i;
	char	*result;

	i = 0;
	if (finish < 0)
		finish = ft_strlen_g(str);
	len = finish - start;
	result = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		result[i] = str[start];
		start++;
		i++;
	}
	result[i] = 0;
	// printf("res: %s len+1: %d\n", result, len + 1);
	return (result);
}

char	**ft_split_by_pipe(char *str) // Выполняем первый пункт, создаем чармасс двойной
{
	int		*coordinates;
	char	**result;
	int		i;
	int		mass_size;

	i = 0;
	mass_size = 0;
	coordinates = take_coordinates(str);
	while (coordinates[i] != -1)
		i++;
	mass_size = i + 1;
	result = malloc(sizeof(char *) * (mass_size + 1));
	result[0] = ft_cutstr(str, 0, coordinates[0]);
	// printf("%d\n", i);
	i = 1;
	while (i < mass_size)
	{
		result[i] = ft_cutstr(str, coordinates[i - 1] + 1, coordinates[i]);
		i++;
	}
	result[i] = NULL;
	// printf("%d\n", i);
	free(coordinates);
	return (result);
}
