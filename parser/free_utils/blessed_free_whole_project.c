/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_free_whole_project.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:12:19 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 21:12:20 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstclear_env(t_env **lst, void (*del)(void *))
{
	t_env	*tmp;

	tmp = *lst;
	(*del)(tmp->content);
	(*del)(tmp->next);
	free(tmp);
	*lst = NULL;
}

t_env	*ft_lstprelast_env(t_env *lst)
{
	t_env	*tmp;
	t_env	*pre;

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

void	list_free_env(t_env **env)
{
	t_env	*last;
	t_env	*pre;
	int			i;
	int			lst_size;

	i = 0;
	lst_size = ft_lstsize_env(*env);
	while (i < lst_size)
	{
		last = ft_lstlast_env(*env);
		pre = ft_lstprelast_env(*env);
		ft_lstclear_env(&last, &free);
		pre->next = NULL;
		i++;
	}
}

void	ft_free_path(t_data *data)
{
	int	i;

	i = -1;
	while (data->path[++i])
		free(data->path[i]);
	if (data->path)
		free(data->path);
	data->path = NULL;
}

void	free_whole_project(t_data *data)
{
	int	i;

	i = -1;
	free(data->current_env);
	ft_free_for_export(data);
	list_free_env(&data->head_env);
	free(data->current_pwd);
	free(data->current_oldpwd);
	if (data->path)
	{
		while (data->path[++i])
			free(data->path[i]);
		free(data->path);
	}
	close(data->fd_mother);
}
