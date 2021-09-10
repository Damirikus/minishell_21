#include "libft.h"

t_redirect	*ft_lstnew_redirect(void)
{
	t_redirect	*begin;

	begin = (t_redirect *) malloc(sizeof(t_redirect));
	if (!begin)
		return (NULL);
	begin->flag_for_stdin = 0;
    begin->flag_for_stdout = 0;
    begin->filename = NULL;
    begin->flag = 0;
    begin->next = NULL;
	return (begin);
}