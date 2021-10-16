#include "minishell.h"

void	dollar_cut_from_str_redirect(char **str, int start, int finish)
{
	char	*result;
	char	*tmp;
	int		i;

	tmp = *str;
	result = malloc(sizeof(char) * (strlen(tmp) - (finish - start + 1) + 1)); // Искать здесь
	i = 0;
	while (i < start)
	{
		result[i] = tmp[i];
		i++;
	}
	finish++;
	while (tmp[finish])
	{
		result[i] = tmp[finish];
		i++;
		finish++;
	}
	result[i] = '\0';
	free(*str);
	*str = result;
}

void	dollar_pull_swaper_redirect(char **str, char *value, int start)
{
	char	*result;
	char	*tmp;
	int		finish;
	int		i;
	int		j;

	tmp = *str;
	start--;
	finish = start + 1;
	while (isalnum(tmp[finish]) || tmp[finish] == '_')
		finish++;
	result = malloc(sizeof(char) * (strlen(tmp) - (finish - start) + strlen(value) + 1));
	i = 0;
	while (i < start)
	{
		result[i] = tmp[i];
		i++;
	}
	j = 0;
	while (j < strlen(value))
	{
		result[i] = value[j];
		i++;
		j++;
	}
	while (tmp[finish])
	{
		result[i] = tmp[finish];
		finish++;
		i++;
	}
	// while(1);
	result[i] = 0;
	free(*str);
	free(value);
	*str = result;
}

void	dollar_pull_exit_code_redirect(char **str, int start)
{
	char	*result;
	char	*tmp;
	char	*exit_code_str;
	int		i;
	int		j;

	exit_code_str = ft_itoa(code_exit);
	tmp = *str;
	result = malloc(sizeof(char) * (ft_strlen(tmp) - 2 + ft_strlen(exit_code_str) + 1));
	i = 0;
	j = 0;
	while (i < start)
	{
		result[i] = tmp[i];
		i++;
	}
	while (exit_code_str[j])
	{
		result[i] = exit_code_str[j];
		j++;
		i++;
	}
	start += 2;
	while (tmp[start])
	{
		result[i] = tmp[start];
		start++;
		i++;
	}
	result[i] = 0;
	free(*str);
	*str = result;
	free(exit_code_str);
}

void	dollar_pull_helper_redirect(char **str, int j, char **env) // Встретили знак даллара в строке, пробуем менять
{
	int		start;
	int		i;
	char	*key;
	char	*value;
	char	*tmp;

	start = j + 1;
	value = NULL;
	j++;
	tmp = *str;
	if (tmp[start] == '?')
	{
		dollar_pull_exit_code_redirect(str, j - 1);
		return ;
	}
	while (isalnum(tmp[j]) || tmp[j] == '_')
		j++;
	key = ft_cutstr(tmp, start, j);
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
		dollar_pull_swaper_redirect(str, value, start);
	else
		dollar_cut_from_str_redirect(str, start - 1, j - 1);
}

void	dollar_pull_special_skip_redirect(char **str, int *j, char **env)
{
	char	*tmp;

	tmp = *str;
	*j = *j + 1;
	while (tmp[*j] != '\"' && tmp[*j] != '\0')
	{
		if (tmp[*j] == '$' && (isalnum(tmp[*j + 1]) || tmp[*j + 1] == '_' || tmp[*j + 1] == '?'))
		{
			dollar_pull_helper_redirect(str, *j, env);
			*j = -1;
			return ;
		}
		*j = *j + 1;
	}
	*j = *j + 1;
}

int	dollar_pull_redirect(t_redirect *head_redirect, char **env) //Второй пункт, раскрываем даллары
{
	int		j;
	t_redirect	*tmp;

	j = 0;
	tmp = head_redirect;
	while (tmp)
	{
		j = 0;
		while (tmp->filename[j])
		{
			if (j != -1 && tmp->filename[j] == '\"')
				dollar_pull_special_skip_redirect(&tmp->filename, &j, env);
			if (j != -1 && tmp->filename[j] == '\'')
				ft_skip_quotes(tmp->filename, &j);
			if (j != -1 && tmp->filename[j] == '$' && (isalnum(tmp->filename[j + 1]) || tmp->filename[j + 1] == '_' || tmp->filename[j + 1] == '"' || tmp->filename[j + 1] == '?'))
			{
				dollar_pull_helper_redirect(&tmp->filename, j, env);
				j = -1;
			}
			if (j == -1 || (tmp->filename[j] != '\'' && tmp->filename[j] != '\0'))
				j++;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	dollar_pull_for_redirect(t_list *head_command, char **env)
{
	t_list	*tmp;

	tmp = head_command;
	while (tmp)
	{
		if (!dollar_pull_redirect(tmp->head_redirect, env))
			tmp = tmp->next;
	}
}