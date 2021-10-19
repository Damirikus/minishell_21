/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:25:43 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:25:44 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_redirect(t_redirect **lst, void (*del)(void *))
{
	t_redirect	*tmp;

	tmp = *lst;
	(*del)(tmp->filename);
	(*del)(tmp->next);
	free(tmp);
	*lst = NULL;
}
