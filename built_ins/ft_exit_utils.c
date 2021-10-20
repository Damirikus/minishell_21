/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:59:06 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/19 22:33:34 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_exit(t_data *data, int len, long code)
{
	if (len == 1)
	{
		free_whole_project(data);
		exit(code % 256);
	}
	else
		return (0);
}

int	ft_exit_part2(t_data *data)
{
	printf("minishell: exit: too many arguments\n");
	data->code_exit = 1;
	return (0);
}

int	ft_check_max_min(char *str)
{
	char	*buf;
	int		i;

	i = 0;
	if (ft_strlen(str) < 19)
		return (1);
	if (str[i] == 45)
		i++;
	if (i == 1)
	{
		buf = "9223372036854775808";
		if (ft_strcmp(buf, str + 1) < 0)
			return (0);
	}
	else
	{
		buf = "9223372036854775807";
		if (ft_strcmp(buf, str) < 0)
			return (0);
	}
	return (1);
}
