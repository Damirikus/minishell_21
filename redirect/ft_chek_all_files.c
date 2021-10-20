/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chek_all_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:38:57 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/20 21:23:48 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chek_all_files(t_list *list, t_data *data)
{
	t_list		*current;
	t_redirect	*redent;
	int			len;

	if (ft_key_handler_creat(list, data))
		return (-1);
	len = 0;
	current = list;
	while (current)
	{
		len++;
		if (current->head_redirect)
		{
			redent = current->head_redirect;
			while (redent)
			{
				ft_creat_chek_files(current, redent, data);
				redent = redent->next;
			}
		}
		current = current->next;
	}
	return (len);
}
