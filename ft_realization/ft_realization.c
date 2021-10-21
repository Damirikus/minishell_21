/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:00:02 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/21 16:16:15 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_realization_mother(t_list *list, t_data *data)
{
	if (data->len > 1 && !list->next && data->flat % 2 == 0)
		close(data->b[0]);
	else if (data->len > 1 && !list->next && data->flat % 2 == 1)
		close(data->a[0]);
	if (data->flat % 2 == 0 && list->flag_for_pipe == 1)
	{
		if (data->b[0])
			close(data->b[0]);
		close(data->a[1]);
	}
	else if (data->flat % 2 == 1 && list->flag_for_pipe == 1)
	{
		if (data->a[0])
			close(data->a[0]);
		close(data->b[1]);
	}
	ft_closer(list);
	data->flat++;
}

int	ft_realization_part(t_list *list, t_data *data)
{
	int	p[2];

	if (data->a[0])
		close(data->a[0]);
	if (data->b[0])
		close(data->b[0]);
	if (data->len > 1 && list->next)
	{
		pipe(p);
		close(p[1]);
		if (list->next->fd0 == -1)
			list->next->fd0 = p[0];
		else
			close(p[0]);
	}
	printf("minishell: %s: No such file or directory\n", list->filename_for_job);
	ft_closer(list);
	data->code_exit = 1;
	return (0);
}

int	ft_realization_part_last(t_list *list, t_data *data, int *flag)
{
	int	pid;

	pid = 0;
	if (!ft_strcmp(list->cmd[0], "export") && list->cmd[1] != NULL)
		ft_export(data, list);
	else if (!ft_strcmp(list->cmd[0], "unset"))
		ft_unset(data, list);
	else
	{
		if (data->flat % 2 == 0 && list->flag_for_pipe == 1)
			pipe(data->a);
		else if (data->flat % 2 == 1 && list->flag_for_pipe == 1)
			pipe(data->b);
		pid = fork();
		*flag = 1;
		if (pid == 0)
			ft_realization_daughter(list, data);
		if (pid != 0)
			ft_realization_mother(list, data);
	}
	return (pid);
}

int	ft_realization(t_list *list, t_data *data)
{
	int	pid;
	int	flag;

	flag = 0;
	if (g_f == 1)
		return (0);
	if (list->flag_for_job == 1)
		return (ft_realization_part(list, data));
	if (list->cmd[0])
	{
		ft_check_bild_func(list, data);
		if (!ft_strcmp(list->cmd[0], "exit"))
			ft_exit(list, data->len, data);
		else if (!ft_strcmp(list->cmd[0], "cd"))
			ft_cd(list, data);
		else
			pid = ft_realization_part_last(list, data, &flag);
		if (flag == 1)
			return (pid);
		else
			return (1337);
	}
	else
		ft_closer(list);
	return (0);
}
