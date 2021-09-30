#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	// есть что удалит
	(*del)(tmp->next);
	free(tmp);
	*lst = NULL;
}
