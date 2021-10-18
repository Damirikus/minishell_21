/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_putter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:53:12 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 21:44:53 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_flag_putter(t_list **head_command)
{
	t_list	*tmp;

	tmp = ft_lstlast(*head_command);
	tmp->flag_for_pipe = 0;
}

void	redirect_flag_putter_helper(t_redirect **tmp, t_redirect \
**prev_in, t_redirect **prev_out)
{
	t_redirect	*new_tmp;
	t_redirect	*new_prev_in;
	t_redirect	*new_prev_out;

	new_tmp = *tmp;
	new_prev_in = *prev_in;
	new_prev_out = *prev_out;
	if (new_tmp->flag_for_stdin)
	{
		if (new_prev_in)
			new_prev_in->flag = 0;
		*prev_in = new_tmp;
		new_tmp->flag = 1;
	}
	else if (new_tmp->flag_for_stdout)
	{
		if (new_prev_out)
			new_prev_out->flag = 0;
		*prev_out = new_tmp;
		if (new_tmp->flag_for_strange == 0)
			new_tmp->flag = 1;
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
		redirect_flag_putter_helper(&tmp, &prev_in, &prev_out);
		tmp = tmp->next;
	}
}
