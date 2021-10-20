/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:42:20 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/19 22:11:57 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_key_handler_creat(t_list *list, t_data *data)
{
	t_list		*current;
	t_redirect	*redent;

	current = list;
	while (current)
	{
		if (current->head_redirect)
		{
			redent = current->head_redirect;
			while (redent)
			{
				if (g_f == 1)
					return (1);
				if (redent->flag_for_stdin == 2)
					ft_key_handler(current, redent, data);
				redent = redent->next;
			}
			if (g_f == 2)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_creat_chek_files(t_list *list, t_redirect *redirect, t_data *data)
{
	(void)data;
	if (redirect->flag_for_stdout == 1 && list->flag_for_job == 0)
	{
		if (ft_stdout(list, redirect))
			return (1);
	}
	else if (redirect->flag_for_stdout == 2 && list->flag_for_job == 0)
	{
		if (ft_stdoutout(list, redirect))
			return (1);
	}
	else if (redirect->flag_for_stdin == 1 && list->flag_for_job == 0)
	{
		if (!ft_stdin(list, redirect))
			return (1);
	}
	return (0);
}

int	ft_stdout(t_list *list, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		list->flag_for_job = 1;
		list->filename_for_job = redirect->filename;
		return (1);
	}
	if (redirect->flag == 1)
		list->fd1 = fd;
	else
		close(fd);
	return (0);
}

int	ft_stdoutout(t_list *list, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		list->flag_for_job = 1;
		list->filename_for_job = redirect->filename;
		return (1);
	}
	if (redirect->flag == 1)
		list->fd1 = fd;
	else
		close(fd);
	return (0);
}

int	ft_stdin(t_list *list, t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		list->flag_for_job = 1;
		list->filename_for_job = redirect->filename;
		return (0);
	}
	if (redirect->flag == 1)
		list->fd0 = fd;
	else
		close(fd);
	return (1);
}
