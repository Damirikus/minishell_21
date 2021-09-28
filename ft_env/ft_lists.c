#include "minishell.h"

int ft_lstsize(t_env *lst)
{
	t_env *tmp;
	int i;
	
	i = 0;
	tmp = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_env *ft_lstlast(t_env *lst)
{
	t_env *tmp;
	
	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env *last;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->next = NULL;
}


t_env *ft_lstnew_initial(char *content)
{
	t_env *result;
	
	if (!(result = malloc(sizeof(t_env))))
		return (NULL);
	result->sys = 1;
	result->content = ft_strdup(content);
	result->next = NULL;
	return (result);
}

void	print_env(t_env *head)
{
	t_env *tmp;
	
	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
