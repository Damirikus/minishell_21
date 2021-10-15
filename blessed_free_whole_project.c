#include "minishell.h"

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

// t_env	*ft_lstlast_env(t_env *lst)
// {
// 	t_env	*tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		if (tmp->next == NULL)
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	return (tmp);
// }

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

void	free_whole_project(t_data *data) // data->path?
{
	int	i;

	i = -1;
	free(data->current_env);
	ft_free_for_export(data);
	list_free_env(&data->head_env);
	free(data->current_pwd);
	free(data->current_oldpwd);
	while (data->path[++i])
		free(data->path[i]);
	close(data->fd_mother);
	free(data->path);
}
