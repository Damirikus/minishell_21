#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char* input;
	t_list *list;
	t_list *new;
	t_list *ff;
	t_list *current;
	

	
	char *cmdd[] = {"wc","-l", NULL};
	// char *cmdd2[] = {"pwd", NULL};
	// char *cmdd2[] = {"wc", "-l", NULL};
	char *str = "1";

	


	list = ft_lstnew(cmdd, env);
	// new = ft_lstnew(cmdd2, env);
	// list->next = new;
	// ff = ft_lstnew(cmdd3, env);
	list->filename = str;
	// list->next = ff;




	char **path;
	path = ft_path(getenv("PATH"));


//	char shell_prompt[100];
	while(1)
	{
		// getting the current user's path
//		snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));
		input = readline("miniHELL %> ");
		if (!input)
			break;
		// path autocompletion when tabulation hit
		rl_bind_key('\t', rl_complete);
		// adding the previous input into history
		add_history(input);



        //на этом этапе происходит парс, на выходе лист со всеми командами


		
		// list->flag_for_pipe = 1;
		// list->next->flag_for_pipe = -1;
		list->flag_for_stdin = 2;
		// list->flag_for_stdout = 2;
		
		
		/* далее полученный лист отправляем в цикле на исполнение
        в зависимотсти какой флаг, лист будет отправяться в соответсвующую функцию
        во всех функциях создаетя дочерний процесс, который после исполнения будет завершаться
        на исполнение все листы, после создания дочернего процесса, отправляются в функцию ft_distributor 
        */ 
		
		current = list;
		while(current)
		{
			if (current->flag_for_pipe == 1)
			{
				ft_pipe(path, current);
			}
			// else if (current->flag_for_pipe == -1)
			// {
			// 	ft_empty(path, current);
			// 	dup2(list->pid_mother, 0);
			// }
			else if (current->flag_for_stdout > 0)
			{
				ft_stdout(path, current);
			}
			else if (current->flag_for_stdin == 1)
			{
				ft_stdin(path, current);
			}
            else if (current->flag_for_stdin == 2)
			{
				ft_stdin2(path, current);
			}
			else
			{
				ft_empty(path, current);
				dup2(list->pid_mother, 0);
			}
			current = current->next;
		}

		/* do stuff */

		// Т. к. вызов readline() выделяет память, но не освобождает (а возвращает), то эту память нужно вернуть (освободить).
		free(input);

	}
}


int ft_empty(char **path, t_list *list)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		ft_distributor(path, list);
	}
	if (pid != 0)
	{
		wait(NULL);
	}
	return (0);
}
