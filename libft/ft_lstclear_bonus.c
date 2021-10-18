#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	(*del)(tmp->next);
	free(tmp);
	*lst = NULL;
}
