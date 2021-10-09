#include "libft.h"

t_redirect	*ft_lstlast_redirect(t_redirect *lst)
{
	t_redirect	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
