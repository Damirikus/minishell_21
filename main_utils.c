/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:39:05 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/21 12:33:00 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initial_loop_setting(t_data *data)
{
	data->a[0] = -10000;
	data->a[1] = -10000;
	data->b[0] = -10000;
	data->b[1] = -10000;
	data->pids = NULL;
	g_f = 0;
	if (data->td[0])
		close(data->td[0]);
	if (data->td[1])
		close(data->td[1]);
	data->td[0] = -10000;
	data->td[1] = -10000;
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	rl_getc_function = data->sg;
}

void	main_helper(t_data *data, int i, int status, int pid)
{
	t_list	*current;

	current = data->head_command;
	while (current)
	{
		if (g_f == 1)
			return ;
		pid = ft_realization(current, data);
		data->pids[++i] = pid;
		current = current->next;
	}
	i = -1;
	if (pid != -99)
	{
		while (++i < data->len)
		{
			if (data->pids[i] != 0)
			{
				if (waitpid(data->pids[i], &status, 0) != data->pids[i])
					status = -1;
			}
			if (status != -1)
				data->code_exit = status / 256;
		}
	}
}

void	main_sleep_and_close(t_data *data)
{
	int	i;
	int	pid;
	int	status;

	i = -1;
	status = 0;
	pid = 0;
	data->pids = malloc(sizeof(int) * data->len);
	data->flat = 0;
	main_helper(data, i, status, pid);
	usleep(10000);
	if (data->td[0])
		close(data->td[0]);
	if (data->td[1])
		close(data->td[1]);
}

void	signals_and_add_history(char *input, t_data *data)
{
	if (*input)
		add_history(input);
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, ft_hz);
	rl_getc_function = data->sg;
}

int	preparation_main(char *input, t_data *data)
{
	t_list	*current;

	if (!preparser(input, data))
	{
		data->head_command = parser(input, data);
		data->len = ft_chek_all_files(data->head_command, data);
		if (data->len == -1)
		{
			current = data->head_command;
			while (current)
			{
				ft_closer(current);
				current = current->next;
			}
			if (input)
				free(input);
			return (1);
		}
		main_sleep_and_close(data);
	}
	return (0);
}
