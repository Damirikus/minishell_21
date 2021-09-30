#include "libft.h"

int	ft_lstsize_redirect(t_redirect *lst)
{
	t_redirect	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}