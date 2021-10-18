#include "libft.h"

void	ft_lstclear_redirect(t_redirect **lst, void (*del)(void *))
{
	t_redirect	*tmp;

	tmp = *lst;
	(*del)(tmp->filename);
	(*del)(tmp->next);
	free(tmp);
	*lst = NULL;
}
