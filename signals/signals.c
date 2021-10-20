/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:02:41 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/19 22:11:57 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_ctrlc(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_ctrl(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	ft_hz(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
}

void	ft_emp(int sig)
{
	(void)sig;
	g_f = 1;
	write(1, "\e[C", 3);
}
