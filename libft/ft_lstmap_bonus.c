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
