/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distributor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:38:53 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/21 16:50:15 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closer(t_list *list)
{
	if (list->fd0 != -1)
		close(list->fd0);
	if (list->fd1 != -1)
		close(list->fd1);
}

void	ft_check_bild_func(t_list *list, t_data *data)
{
	int	p[2];

	if ((!ft_strcmp(list->cmd[0], "exit") || !ft_strcmp(list->cmd[0], "cd") \
		|| (!ft_strcmp(list->cmd[0], "export") && list->cmd[1]) \
		|| !ft_strcmp(list->cmd[0], "unset")) \
		&& (list->flag_for_pipe == 1 \
		&& data->len > 1 && list->flag_for_job == 0))
	{
		pipe(p);
		close(p[1]);
		if (list->next->fd0 == -1)
			list->next->fd0 = p[0];
	}
	if ((!ft_strcmp(list->cmd[0], "exit") || !ft_strcmp(list->cmd[0], "cd") \
		|| (!ft_strcmp(list->cmd[0], "export") && list->cmd[1]) \
		|| !ft_strcmp(list->cmd[0], "unset")) \
		&& (list->flag_for_pipe == 0 \
		&& data->len > 1 && list->flag_for_job == 0))
	{
		if (data->a[0])
			close(data->a[0]);
		if (data->b[0])
			close(data->b[0]);
	}
}

int	ft_distributor(t_list *list, t_data *data)
{
	char	*full_path;

	full_path = ft_make_path(data->path, list);
	if (!ft_strcmp(list->cmd[0], "echo"))
		ft_echo(list);
	else if (!ft_strcmp(list->cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(list->cmd[0], "env"))
		print_2d_massive(data->current_env, list, data);
	else if (!ft_strcmp(list->cmd[0], "export"))
		print_2d_massive(data->current_export, list, data);
	else
		ft_distributor_part(list, data, full_path);
	ft_closer(list);
	exit(0);
}

void	ft_distributor_part(t_list *list, t_data *data, char *full_path)
{
	if (execve(full_path, list->cmd, data->execve_env) == -1)
	{
		dup2(data->fd_mother, 1);
		close(data->fd_mother);
		if (list->cmd[0][0] == '/' || (list->cmd[0][0] == '.'
				&& list->cmd[0][1] == '/'))
			printf("minishell: %s: no such file or directory\n", list->cmd[0]);
		else
			printf("minishell: %s: command not found\n", list->cmd[0]);
		ft_closer(list);
		exit (127);
	}
}
