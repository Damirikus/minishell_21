#include "minishell.h"

void	ft_print_list(t_list *head_command) 
{
	t_list		*tmp;
	t_redirect	*redirect;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = head_command;
	while (tmp)
	{
		printf("lst_number: %d\n\n", i);
		if (tmp->head_redirect)
		{
			redirect = tmp->head_redirect;
			printf("Redirects:\n\n");
			j = 0;
			while (redirect)
			{
				printf("%d: stdin: %d stdout: %d flag: %d name: |%s|\n\n", j, redirect->flag_for_stdin, redirect->flag_for_stdout, redirect->flag, redirect->filename);
				redirect = redirect->next;
				j++;
			}
		}
		printf("flag_for_pipe: %d\n******************\n", tmp->flag_for_pipe);
		tmp = tmp->next;
		i++;
	}
}