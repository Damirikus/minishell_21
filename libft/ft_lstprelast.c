#include "libft.h"

t_list	*ft_lstprelast(t_list *lst)
{
	t_list	*tmp;
	t_list	*pre;

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
