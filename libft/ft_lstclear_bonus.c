#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;

	if (!*lst)
		return ;
	while (*lst != NULL)
	{
		current = (*lst)->next;
		del((*lst)->cmd);
		free(*lst);
		*lst = current;
	}
}
