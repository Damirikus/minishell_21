/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:39:20 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 21:11:12 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	list_free_redirect(t_redirect **redirect)
{
	t_redirect	*last;
	t_redirect	*pre;
	int			i;
	int			lst_size;

	i = 0;
	lst_size = ft_lstsize_redirect(*redirect);
	while (i < lst_size)
	{
		last = ft_lstlast_redirect(*redirect);
		pre = ft_lstprelast_redirect(*redirect);
		ft_lstclear_redirect(&last, &free);
		pre->next = NULL;
		i++;
	}
}

void	list_free_command(t_list **head)
{
	t_list	*last;
	t_list	*pre;
	int		i;
	int		lst_size;

	i = 0;
	lst_size = ft_lstsize(*head);
	while (i < lst_size)
	{
		last = ft_lstlast(*head);
		pre = ft_lstprelast(*head);
		ft_lstclear(&last, &free);
		pre->next = NULL;
		i++;
	}
	*head = NULL;
}

void	list_free_redirect_cmd(t_list *tmp)
{
	int	i;

	i = 0;
	while (tmp->cmd[i])
	{
		free(tmp->cmd[i]);
		i++;
	}
	free(tmp->cmd);
	list_free_redirect(&tmp->head_redirect);
}

void	list_free(t_list **head)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		list_free_redirect_cmd(tmp);
		tmp = tmp->next;
	}
	list_free_command(head);
}
