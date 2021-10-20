/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:39:01 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/19 22:35:19 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_key_handler_2(void *sg, t_redirect *redirect)
{
	char	*tmp;

	(void)sg;
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (!ft_strcmp(tmp, redirect->filename))
		{
			free(tmp);
			g_f = 0;
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int	ft_key_handler_3_part(char *str, t_data *data)
{
	free(str);
	close(data->td[1]);
	rl_getc_function = data->sg;
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, ft_hz);
	g_f = 0;
	return (0);
}

int	ft_key_handler_4(char *str, t_data *data)
{
	close(data->td[0]);
	dup2(data->td[1], 1);
	close(data->td[1]);
	printf("%s\n", str);
	free(str);
	exit(0);
}

int	ft_key_handler_3(t_redirect *redirect, t_data *data)
{
	char	*str;
	int		pid;

	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (!ft_strcmp(str, redirect->filename))
			return (ft_key_handler_3_part(str, data));
		pid = fork();
		if (pid == 0)
			ft_key_handler_4(str, data);
		if (pid != 0)
		{
			wait(NULL);
			free(str);
		}
	}
	return (0);
}

int	ft_key_handler(t_list *list, t_redirect *redirect, t_data *data)
{
	g_f = 2;
	signal(SIGINT, ft_emp);
	signal(SIGQUIT, SIG_IGN);
	rl_getc_function = getc;
	if (redirect->flag == 0)
		return (ft_key_handler_2(data->sg, redirect));
	else if (redirect->flag == 1)
	{
		pipe(data->td);
		list->fd0 = data->td[0];
		return (ft_key_handler_3(redirect, data));
	}
	return (0);
}
