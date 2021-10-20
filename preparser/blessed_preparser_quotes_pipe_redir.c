/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_preparser_quotes_pipe_redir.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:20:49 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/20 15:42:01 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes_skip(char *str, int *i, int code, t_data *data)
{
	if (code == 2)
	{
		while (str[*i] != '\"' && str[*i] != '\0')
			*i = *i + 1;
		if (str[*i] == '\0')
			return (ft_error(1, data));
		else
			*i = *i + 1;
	}
	else if (code == 1)
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i + 1;
		if (str[*i] == '\0')
			return (ft_error(1, data));
		else
			*i = *i + 1;
	}
	return (0);
}

int	check_quotes(char *str, int *i, t_data *data)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		if (check_quotes_skip(str, i, 2, data))
			return (1);
	}
	if (str[*i] == '\'')
	{
		*i = *i + 1;
		if (check_quotes_skip(str, i, 1, data))
			return (1);
	}
	return (0);
}

int	check_pipe(char *str, int *i, t_data *data)
{
	int	j;

	j = 0;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '|')
		return (ft_error(2, data));
	j = *i + 1;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '|')
		return (ft_error(2, data));
	if (str[j] == '\0')
		return (ft_error(3, data));
	return (0);
}

int	check_redir(char *str, int *i, t_data *data)
{
	int	j;

	if (str[*i] == '>' && str[*i + 1] == '<')
		return (ft_error(4, data));
	if ((str[*i] == '>' && str[*i + 1] == '|'))
		return (ft_error(5, data));
	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' \
	&& str[*i + 1] == '>') || (str[*i] == '<' && str[*i + 1] == '>'))
		j = *i + 2;
	else
		j = *i + 1;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '\0')
		return (ft_error(5, data));
	if (str[j] == '|')
		return (ft_error(2, data));
	if (str[j] == '<')
		return (ft_error(4, data));
	if (str[j] == '>')
		return (ft_error(6, data));
	return (0);
}

int	check_pipe_redir(char *str, int *i, t_data *data)
{
	if (str[*i] == '|')
		return (check_pipe(str, i, data));
	if (str[*i] == '<' || str[*i] == '>')
		return (check_redir(str, i, data));
	return (0);
}
