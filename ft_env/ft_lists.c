#include "minishell.h"

int ft_lstsize(t_list *lst)
{
	t_list *tmp;
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

t_list *ft_lstlast(t_list *lst)
{
	t_list *tmp;
	
	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->next = NULL;
}


t_list *ft_lstnew_initial(char *content)
{
	t_list *result;
	
	if (!(result = malloc(sizeof(t_list))))
		return (NULL);
	result->sys = 1;
	result->content = ft_strdup(content);
	result->next = NULL;
	return (result);
}

void	print_list(t_list *head)
{
	t_list *tmp;
	
	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
