/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_list_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:42:04 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/19 14:40:03 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_initial_env(char *content)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		ft_error(8, NULL);
	result->sys = 1;
	result->content = ft_strdup(content);
	result->next = NULL;
	return (result);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_env(*lst);
	last->next = new;
	new->next = NULL;
}

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

int	ft_lstsize_env(t_env *lst)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
