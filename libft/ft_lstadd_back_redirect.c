#include "libft.h"

void ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_redirect(*lst);
	last->next = new;
	new->next = NULL;
}