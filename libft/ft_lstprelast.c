/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprelast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:03 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:04 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstprelast(t_list *lst)
{
	t_list	*tmp;
	t_list	*pre;

	tmp = lst;
	pre = tmp;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (pre);
		pre = tmp;
		tmp = tmp->next;
	}
	return (pre);
}
