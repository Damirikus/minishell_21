/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_dollar_pull.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:55:50 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 18:45:20 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dollar_pull_exit_code(char **pipe_mass, int number, \
int start, t_data *data)
{
	char	*result;
	char	*exit_code_str;
	int		i;
	int		j;

	exit_code_str = ft_itoa(data->code_exit);
	result = malloc(sizeof(char) * (ft_strlen(pipe_mass[number]) \
	- 2 + ft_strlen(exit_code_str) + 1));
	i = -1;
	j = -1;
	while (++i < start)
		result[i] = pipe_mass[number][i];
	while (exit_code_str[++j])
		result[i++] = exit_code_str[j];
	start += 1;
	while (pipe_mass[number][++start])
		result[i++] = pipe_mass[number][start];
	result[i] = 0;
	free(pipe_mass[number]);
	pipe_mass[number] = result;
	free(exit_code_str);
}

char	*dollar_pull_helper_value_maker(char *pipe_mass, int start, int *j, \
t_data *data)
{
	char	*value;
	char	*key;
	int		i;

	value = NULL;
	while (isalnum(pipe_mass[*j]) || pipe_mass[*j] == '_')
		*j = *j + 1;
	key = ft_cutstr(pipe_mass, start, *j);
	i = -1;
	while (data->current_env[++i])
	{
		if (!strncmp(data->current_env[i], key, strlen(key)) \
		&& data->current_env[i][strlen(key)] == '=')
		{
			value = strdup(data->current_env[i] + strlen(key) + 1);
			break ;
		}
	}
	free(key);
	return (value);
}

void	dollar_pull_helper(char **pipe_mass, int number, int j, t_data *data)
{
	int		start;
	char	*key;
	char	*value;

	start = j + 1;
	value = NULL;
	j++;
	if (pipe_mass[number][start] == '?')
	{
		dollar_pull_exit_code(pipe_mass, number, j - 1, data);
		return ;
	}
	value = dollar_pull_helper_value_maker(pipe_mass[number], start, &j, data);
	if (value != NULL)
		dollar_pull_swaper(pipe_mass, number, value, start);
	else
		dollar_cut_from_str(pipe_mass, number, start - 1, j - 1);
}

void	dollar_pull_special_skip(char **pipe_mass, int i, int *j, t_data *data)
{
	*j = *j + 1;
	while (pipe_mass[i][*j] != '\"' && pipe_mass[i][*j] != '\0')
	{
		if (pipe_mass[i][*j] == '$' && \
		(ft_isalnum_strong(pipe_mass[i][*j + 1], 2)))
		{
			dollar_pull_helper(pipe_mass, i, *j, data);
			*j = -1;
			return ;
		}
		*j = *j + 1;
	}
	*j = *j + 1;
}

void	dollar_pull(char **pipe_mass, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (pipe_mass[++i])
	{
		j = 0;
		while (pipe_mass[i][j])
		{
			if (j != -1 && pipe_mass[i][j] == '\"')
				dollar_pull_special_skip(pipe_mass, i, &j, data);
			if (j != -1 && pipe_mass[i][j] == '\'')
				ft_skip_quotes(pipe_mass[i], &j);
			if (j != -1 && pipe_mass[i][j] == '$' && \
			(ft_isalnum_strong(pipe_mass[i][j + 1], 1)))
			{
				dollar_pull_helper(pipe_mass, i, j, data);
				j = -1;
			}
			if (j == -1 || (pipe_mass[i][j] != '\'' && pipe_mass[i][j] != '\0'))
				j++;
		}
	}
}
