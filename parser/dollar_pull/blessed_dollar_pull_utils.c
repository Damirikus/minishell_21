/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_dollar_pull_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:55:55 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/19 14:02:57 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isalnum_strong(char c, int flag)
{
	if (flag == 1)
	{
		if (ft_isalnum(c) || c == '_' || c == '"' || c == '?')
			return (1);
	}
	else if (flag == 2)
	{
		if (ft_isalnum(c) || c == '_' || c == '_' || c == '?')
			return (1);
	}
	return (0);
}

void	dollar_cut_from_str(char **pipe_mass, int number, int start, int finish)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(pipe_mass[number]) \
	- (finish - start + 1) + 1));
	if (!result)
		ft_error(8, NULL);
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

char	*dollar_pull_swaper_result_maker(char *pipe_mass, \
char *value, int start, int finish)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (ft_strlen(pipe_mass) \
	- (finish - start) + ft_strlen(value) + 1));
	if (!result)
		ft_error(8, NULL);
	i = -1;
	while (++i < start)
		result[i] = pipe_mass[i];
	j = -1;
	while (++j < ft_strlen(value))
		result[i++] = value[j];
	while (pipe_mass[finish])
		result[i++] = pipe_mass[finish++];
	result[i] = 0;
	return (result);
}

void	dollar_pull_swaper(char **pipe_mass, int number, char *value, \
int start)
{
	char	*result;
	int		finish;
	int		i;
	int		j;

	start--;
	finish = start + 1;
	while (ft_isalnum(pipe_mass[number][finish]) || \
	pipe_mass[number][finish] == '_')
		finish++;
	result = dollar_pull_swaper_result_maker(pipe_mass[number], \
	value, start, finish);
	free(pipe_mass[number]);
	free(value);
	pipe_mass[number] = result;
}
