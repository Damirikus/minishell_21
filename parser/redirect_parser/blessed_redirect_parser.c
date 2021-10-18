/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_redirect_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:53:08 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 15:55:40 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_new_command_list(char **pipe_mass, \
t_list **head_command, int number)
{
	t_list	*tmp;
	int		i;

	i = 0;
	ft_lstadd_back(head_command, ft_lstnew(NULL, NULL));
	tmp = ft_lstlast(*head_command);
	while (pipe_mass[number][i])
	{
		if (pipe_mass[number][i] == '\"' || pipe_mass[number][i] == '\'')
			ft_skip_quotes(pipe_mass[number], &i);
		if (pipe_mass[number][i] == '>' || pipe_mass[number][i] == '<')
			add_redirect(pipe_mass[number], tmp, &i);
		if (pipe_mass[number][i] != '\"' && pipe_mass[number][i] != '\'' \
		&& pipe_mass[number][i] != '\0' && pipe_mass[number][i] \
		!= '<' && pipe_mass[number][i] != '>')
			i++;
	}
}

void	redirect_parser(char **pipe_mass, t_list **head_command)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (pipe_mass[i])
	{
		create_new_command_list(pipe_mass, head_command, i);
		i++;
	}
	redirect_cut_from_str(pipe_mass);
	tmp = *head_command;
	while (tmp)
	{
		redirect_flag_putter(tmp);
		tmp = tmp->next;
	}
	pipe_flag_putter(head_command);
}
