#include "libft.h"

t_list	*ft_lstnew(char **content, char **envpe)
{
	t_list	*begin;

	begin = (t_list *) malloc(sizeof(t_list));
	if (!begin)
		return (NULL);
	begin->cmd = content;
	begin->flag_for_pipe = 1;
	begin->fd0 = -1;
	begin->fd1 = -1;
	begin->flag_for_job = 0;
	begin->env = envpe;
	begin->next = NULL;
	begin->head_redirect = NULL;
	begin->filename_for_job = NULL;
	return (begin);
}

