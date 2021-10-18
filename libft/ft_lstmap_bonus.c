/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:25:57 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:25:58 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*curr;

	curr = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->cmd), NULL);
		if (!new)
		{
			ft_lstclear(&curr, del);
			break ;
		}
		ft_lstadd_back(&curr, new);
		lst = lst->next;
	}
	return (curr);
}
