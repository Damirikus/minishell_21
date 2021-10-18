/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_cut_from_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:53:16 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 15:59:19 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*redirect_cutter_result_maker(char *pipe_mass, int start, int i, int j)
{
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen_g(pipe_mass) - (i - start) + 1));
	if (!result)
		ft_error(8, NULL);
	while (j < start)
	{
		result[j] = pipe_mass[j];
		j++;
	}
	while (pipe_mass[i])
	{
		result[j] = pipe_mass[i];
		i++;
		j++;
	}
	result[j] = 0;
	return (result);
}

void	redirect_cutter(char **pipe_mass, int number, int i)
{
	char	*result;
	int		start;
	int		j;

	start = i;
	j = 0;
	while (pipe_mass[number][i] < 33 || pipe_mass[number][i] == '>' \
	|| pipe_mass[number][i] == '<')
		i++;
	while (pipe_mass[number][i] != '\0' && pipe_mass[number][i] > 32 \
	&& pipe_mass[number][i] != '<' && pipe_mass[number][i] != '>')
	{
		if (pipe_mass[number][i] == '\'' || pipe_mass[number][i] == '\"')
			ft_skip_quotes(pipe_mass[number], &i);
		if (pipe_mass[number][i] != '\0' && pipe_mass[number][i] != '\'' \
		&& pipe_mass[number][i] != '\"' \
		&& pipe_mass[number][i] != '>' && pipe_mass[number][i] != '<' && \
		pipe_mass[number][i] > 32)
			i++;
	}
	result = redirect_cutter_result_maker(pipe_mass[number], start, i, j);
	free(pipe_mass[number]);
	pipe_mass[number] = result;
}

void	redirect_cut_from_str(char **pipe_mass)
{
	int	number;
	int	i;

	i = 0;
	number = 0;
	while (pipe_mass[number])
	{
		i = 0;
		while (pipe_mass[number][i])
		{
			if (pipe_mass[number][i] == '\"' || pipe_mass[number][i] == '\'')
				ft_skip_quotes(pipe_mass[number], &i);
			if (pipe_mass[number][i] == '>' || pipe_mass[number][i] == '<')
			{
				redirect_cutter(pipe_mass, number, i);
				i = -1;
			}
			if (i == -1 || (pipe_mass[number][i] != '\"' \
			&& pipe_mass[number][i] != '\'' && pipe_mass[number][i] != '\0'))
				i++;
		}
		number++;
	}
}
