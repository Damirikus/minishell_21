/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realization_daughter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:59:58 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/21 12:33:45 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_realization_daughter_part(t_list *list, t_data *data)
{
	if (data->flat == 0 && list->flag_for_pipe == 1)
	{
		close(data->a[0]);
		if (list->fd1 == -1)
			dup2(data->a[1], 1);
		close(data->a[1]);
	}
	else if (data->flat % 2 == 1 && list->flag_for_pipe == 1)
	{
		if (list->fd0 == -1)
			dup2(data->a[0], 0);
		close(data->a[0]);
		close(data->b[0]);
		if (list->fd1 == -1)
			dup2(data->b[1], 1);
		close(data->b[1]);
	}
	else if (data->flat % 2 == 0 && list->flag_for_pipe == 1)
		ft_realization_daughter_part2(list, data);
}

void	ft_realization_daughter_part2(t_list *list, t_data *data)
{
	if (list->fd0 == -1)
		dup2(data->b[0], 0);
	close(data->b[0]);
	close(data->a[0]);
	if (list->fd1 == -1)
		dup2(data->a[1], 1);
	close(data->a[1]);
}

void	ft_realization_daughter(t_list *list, t_data *data)
{
	if (list->fd0 != -1)
		dup2(list->fd0, 0);
	if (list->fd1 != -1)
		dup2(list->fd1, 1);
	if (!list->next && data->len > 1)
	{
		if (data->flat % 2 == 0)
		{
			if (list->fd0 == -1)
				dup2(data->b[0], 0);
			close(data->b[0]);
		}
		else
		{
			if (list->fd0 == -1)
				dup2(data->a[0], 0);
			close(data->a[0]);
		}
	}
	else
		ft_realization_daughter_part(list, data);
	ft_distributor(list, data);
}
