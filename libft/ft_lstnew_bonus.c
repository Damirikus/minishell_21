#include "libft.h"

t_list	*ft_lstnew(char **content, char **envpe)
{
	t_list	*begin;

	begin = (t_list *) malloc(sizeof(t_list));
	if (!begin)
		return (NULL);
	begin->cmd = content;
	begin->flag_for_pipe = 0;
	// begin->flag_for_stdout = 0;
	// begin->flag_for_stdin = 0;
	begin->pid_mother = dup(0);
	// begin->filename = NULL;
	begin->env = envpe;
	begin->next = NULL;
	begin->head_redirect = NULL;
	return (begin);
}


/*
 * if flag_for_pipe = 1  -  команда до пайпа
 	if flag_for_pipe = -1
 * if flag_for_pipe = 0  -  нет пайпа
 *
 *
 * if flag_for_stdout = 1  -  команда до ">"
 * if flag_for_stdout = 2  -  команда до ">>" 
 * if flag_for_stdout = 0  -  нет stdout
 * 
 * 
 * if flag_for_stdin = 1  -  команда до "<"
 * if flag_for_stdin = 0  -  нет stdin
 * 
 * 
 */
