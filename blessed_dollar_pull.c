#include "minishell.h"

void	dollar_cut_from_str(char **pipe_mass, int number, int start, int finish)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (strlen(pipe_mass[number]) - (finish - start + 1) + 1)); // Искать здесь
	i = 0;
	while (i < start)
	{
		result[i] = pipe_mass[number][i];
		i++;
	}
	finish++;
	while (pipe_mass[number][finish])
	{
		result[i] = pipe_mass[number][finish];
		i++;
		finish++;
	}
	result[i] = '\0';
	free(pipe_mass[number]);
	pipe_mass[number] = result;
}
void	dollar_pull_swaper(char **pipe_mass, int number, char *value, int start)
{
	char	*result;
	int		finish;
	int		i;
	int		j;

	start--;
	finish = start + 1;
	while (isalnum(pipe_mass[number][finish]))
		finish++;
	result = malloc(sizeof(char) * (strlen(pipe_mass[number]) - (finish - start) + strlen(value) + 1));
	i = 0;
	while (i < start)
	{
		result[i] = pipe_mass[number][i];
		i++;
	}
	j = 0;
	while (j < strlen(value))
	{
		result[i] = value[j];
		i++;
		j++;
	}
	while (pipe_mass[number][finish])
	{
		result[i] = pipe_mass[number][finish];
		finish++;
		i++;
	}
	result[i] = 0;
	free(pipe_mass[number]);
	free(value);
	pipe_mass[number] = result;
}

int flah = 0;

void	dollar_pull_helper(char **pipe_mass, int number, int j, char **env) // Встретили знак даллара в строке, пробуем менять
{
	int		start;
	int		i;
	char	*key;
	char	*value;

	start = j + 1;
	value = NULL;
	j++;
	while (isalnum(pipe_mass[number][j]) && pipe_mass[number][j] != 0)
		j++;
	key = ft_cutstr(pipe_mass[number], start, j);
	i = -1;
	while (env[++i])
	{
		if (!strncmp(env[i], key, strlen(key)) && env[i][strlen(key)] == '=')
		{
			value = strdup(env[i] + strlen(key) + 1);
			break ;
		}
	}
	free(key);
	if (value != NULL)
		dollar_pull_swaper(pipe_mass, number, value, start);
	else
		dollar_cut_from_str(pipe_mass, number, start - 1, j - 1);
}

void	dollar_pull_special_skip(char **pipe_mass, int i, int *j, char **env)
{
	*j = *j + 1;
	while (pipe_mass[i][*j] != '\"' && pipe_mass[i][*j] != '\0')
	{
		if (pipe_mass[i][*j] == '$')
		{
			dollar_pull_helper(pipe_mass, i, *j, env);
			*j = -1;
			return ;
		}
		*j = *j + 1;
	}
	*j = *j + 1;
}

void	dollar_pull(char **pipe_mass, char **env) //Второй пункт, раскрываем даллары
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipe_mass[i])
	{
		j = 0;
		while (pipe_mass[i][j])
		{
			if (j != -1 && pipe_mass[i][j] == '\"')
				dollar_pull_special_skip(pipe_mass, i, &j, env);
			if (j != -1 && pipe_mass[i][j] == '\'')
				ft_skip_quotes(pipe_mass[i], &j);
			if (j != -1 && pipe_mass[i][j] == '$')
			{
				dollar_pull_helper(pipe_mass, i, j, env);
				j = -1;
			}
			if (j == -1 || (pipe_mass[i][j] != '\'' && pipe_mass[i][j] != '\0'))
				j++;
		}
		i++;
	}
}
