#include "libft.h"

t_redirect	*ft_lstnew_redirect(int flag, char *name)
{
	t_redirect	*begin;

	begin = (t_redirect *) malloc(sizeof(t_redirect));
	if (!begin)
		return (NULL);
	begin->flag_for_stdin = 0;
	begin->flag_for_stdout = 0;
	if (flag == 1)
		begin->flag_for_stdout = 1;
	if (flag == 2)
		begin->flag_for_stdout = 2;
	if (flag == 3)
		begin->flag_for_stdin = 1;
	if (flag == 4)
		begin->flag_for_stdin = 2;
	begin->filename = name;
	begin->flag = 0;
	begin->next = NULL;
	return (begin);
}