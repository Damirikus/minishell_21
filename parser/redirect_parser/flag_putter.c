/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_putter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:53:12 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 15:54:31 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_flag_putter(t_list **head_command)
{
	t_list	*tmp;

	tmp = ft_lstlast(*head_command);
	tmp->flag_for_pipe = 0;
}

void	redirect_flag_putter_helper(t_redirect *tmp, t_redirect \
*prev_in, t_redirect *prev_out)
{
	if (tmp->flag_for_stdin)
	{
		if (prev_in)
			prev_in->flag = 0;
		prev_in = tmp;
		prev_in->flag = 1;
	}
	else if (tmp->flag_for_stdout)
	{
		if (prev_out)
			prev_out->flag = 0;
		prev_out = tmp;
		if (tmp->flag_for_strange == 0)
			prev_out->flag = 1;
	}
}

void	redirect_flag_putter(t_list *list)
{
	t_redirect	*tmp;
	t_redirect	*prev_in;
	t_redirect	*prev_out;

	prev_in = NULL;
	prev_out = NULL;
	tmp = list->head_redirect;
	while (tmp)
	{
		redirect_flag_putter_helper(tmp, prev_in, prev_out);
		tmp = tmp->next;
	}
}
