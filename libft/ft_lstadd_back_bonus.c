#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (!new)
		return ;
	if (*lst)
	{
		while (current->next)
			current = current->next;
		current->next = new;

	}
	else
		*lst = new;
}
