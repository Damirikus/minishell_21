/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_dollar_pull_redirect_utils.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:37:11 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 20:40:03 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*dollar_pull_helper_value_maker_redirect(char *tmp, \
int start, int *j, t_data *data)
{
	char	*value;
	char	*key;
	int		i;

	value = NULL;
	while (isalnum(tmp[*j]) || tmp[*j] == '_')
		*j = *j + 1;
	key = ft_cutstr(tmp, start, *j);
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

void	dollar_cut_from_str_redirect(char **str, int start, int finish)
{
	char	*result;
	char	*tmp;
	int		i;

	tmp = *str;
	result = malloc(sizeof(char) * (strlen(tmp) - (finish - start + 1) + 1));
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

char	*dollar_pull_swaper_result_maker_redirect(char *tmp, \
char *value, int start, int finish)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (strlen(tmp) - \
	(finish - start) + strlen(value) + 1));
	i = -1;
	while (++i < start)
		result[i] = tmp[i];
	j = -1;
	while (++j < strlen(value))
		result[i++] = value[j];
	while (tmp[finish])
		result[i++] = tmp[finish++];
	result[i] = 0;
	return (result);
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
	result = dollar_pull_swaper_result_maker_redirect(tmp, \
	value, start, finish);
	free(*str);
	free(value);
	*str = result;
}
