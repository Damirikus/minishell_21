#include "libft.h"

t_redirect	*ft_lstprelast_redirect(t_redirect *lst)
{
	t_redirect	*tmp;
	t_redirect	*pre;

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
