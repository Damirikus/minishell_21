/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:02:56 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/20 15:49:29 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_list *list, int len, t_data *data)
{
	int		i;
	long	code;

	code = 0;
	if (len == 1)
		printf("exit\n");
	if (list->fd1 != -1 && len > 1)
		close(list->fd1);
	i = 0;
	if (list->cmd[1])
	{
		if (ft_exit_inner_part(list, i, len, data) == 1)
			return ;
		if (!ft_check_max_min(list->cmd[1]))
			ft_exit_part_inner(list, data, len);
		code = ft_atoi(list->cmd[1]);
	}
	ft_exit_part(code, list, len, data);
}

void	ft_exit_part_inner(t_list *list, t_data *data, int len)
{
	printf("minishell: exit: %s: numeric argument required\n",
		list->cmd[1]);
	if (len == 1)
	{
		free_whole_project(data);
		exit(255);
	}
	else
		return ;
}

int	ft_exit_inner_part(t_list *list, int i, int len, t_data *data)
{
	if (list->cmd[1][0] == 45 || list->cmd[1][0] == 43)
		i++;
	while (list->cmd[1][i])
	{
		if (!ft_isdigit(list->cmd[1][i]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				list->cmd[1]);
			if (len == 1)
			{
				free_whole_project(data);
				exit(255);
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_exit_part(long code, t_list *list, int len, t_data *data)
{
	int	i;

	i = 0;
	while (list->cmd[i])
		i++;
	if (i > 2)
		return (ft_exit_part2(data));
	if (code < 0)
	{
		code *= -1;
		code %= 256;
		code = 256 - code;
		if (len == 1)
		{
			free_whole_project(data);
			exit(code);
		}
		else
			return (0);
	}
	return (ft_exit_exit(data, len, code));
}
