/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:39:05 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/20 18:16:15 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initial_loop_setting(t_data *data)
{
	data->a[0] = 0;
	data->a[1] = 0;
	data->b[0] = 0;
	data->b[1] = 0;
	data->td[0] = 0;
	data->td[1] = 0;
	g_f = 0;
	if (data->td[0])
		close(data->td[0]);
	if (data->td[1])
		close(data->td[1]);
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	rl_getc_function = data->sg;
}

void	main_helper(t_data *data, int i, int status, int pid)
{
	t_list	*current;

	data->flat = 0;
	current = data->head_command;
	while (current)
	{
		pid = ft_realization(current, data);
		data->pids[++i] = pid;
		current = current->next;
	}
	i = 0;
	if (pid != -99)
	{
		while (i < data->len)
		{
			if (data->pids[i] != 0)
			{
				if (waitpid(data->pids[i], &status, 0) != data->pids[i])
					status = -1;
			}
			if (status != -1)
				data->code_exit = status / 256;
			i++;
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
			free(input);
			return (1);
		}
		main_sleep_and_close(data);
	}
	return (0);
}
