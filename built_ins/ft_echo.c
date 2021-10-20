/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:02:51 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/19 22:03:49 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_list *list)
{
	int	qw;
	int	k;

	qw = 0;
	while (list->cmd[qw])
		qw++;
	if (qw == 1)
	{
		write(1, "\n", 1);
		exit(0);
	}
	k = 1;
	if (list->cmd[1])
		k = ft_echo_part_null(list, k, qw);
	if (k == 1)
		ft_echo_part(list, 1, qw);
	else
		ft_echo_part2(list, k, qw);
	exit(0);
}

int	ft_echo_part_null(t_list *list, int k, int qw)
{
	int	i;
	int	flag;

	while (k < qw)
	{
		if (list->cmd[k][0] != '-')
			break ;
		if (list->cmd[k][0] == '-' && !list->cmd[k][1])
			break ;
		i = 1;
		flag = 0;
		while (list->cmd[k][i])
		{
			if (list->cmd[k][i] != 'n')
			{
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag == 1)
			break ;
		k++;
	}
	return (k);
}

void	ft_echo_part(t_list *list, int i, int qw)
{
	int	count;

	while (list->cmd[i])
	{
		count = 0;
		while (list->cmd[i][count])
		{
			write(1, &list->cmd[i][count], 1);
			count++;
		}
		if (i != qw - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	ft_echo_part2(t_list *list, int i, int qw)
{
	int	count;

	while (list->cmd[i])
	{
		count = 0;
		while (list->cmd[i][count])
		{
			write(1, &list->cmd[i][count], 1);
			count++;
		}
		if (i != qw - 1)
			write(1, " ", 1);
		i++;
	}
}
