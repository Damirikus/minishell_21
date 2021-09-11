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
	

	
	char *cmdd[] = {"cat", NULL};
	// char *cmdd2[] = {"pwd", NULL};
	// char *cmdd2[] = {"wc", "-l", NULL};
	// char *str = "1";
	// char *cmdd[] = {NULL};

	list = ft_lstnew(cmdd, env);
	// new = ft_lstnew(cmdd2, env);
	// list->next = new;
	// ff = ft_lstnew(cmdd3, env);
	// list->filename = str;
	// list->next = ff;
	list->head_redirect = ft_lstnew_redirect();
	list->head_redirect->filename = "1";
	list->head_redirect->flag = 1;
	list->head_redirect->flag_for_stdin = 2;

	t_redirect *one;
	one = ft_lstnew_redirect();
	one->filename = "2";
	// // one->flag_for_stdin = 1;
	one->flag = 1;
	one->flag_for_stdout = 2;
	list->head_redirect->next = one;







	char *cmdd2[] = {"wc","-l",  NULL};
	// char *cmdd2[] = {"pwd", NULL};
	// char *cmdd2[] = {"wc", "-l", NULL};
	// char *str = "1";
	// char *cmdd[] = {NULL};

	// list = ft_lstnew(cmdd, env);
	new = ft_lstnew(cmdd2, env);
	list->next = new;
	// ff = ft_lstnew(cmdd3, env);1
	// list->filename = str;
	// list->next = ff;
	list->next->head_redirect = ft_lstnew_redirect();
	list->next->head_redirect->filename = "3";
	list->next->head_redirect->flag = 1;
	list->next->head_redirect->flag_for_stdout = 2;

	// t_redirect *on;
	// on = ft_lstnew_redirect();
	// on->filename = "4";
	// // one->flag_for_stdin = 1;
	// on->flag = 1;
	// on->flag_for_stdout = 2;
	// list->next->head_redirect->next = on;

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
		//  list = ft_pars(input);
		

		//на этом тапе происходит проверка всех файлов и их создание, если листов несколько, то есть есть пайпы
		if (list->next)
			ft_chek_all_files(list);
		
		
		list->flag_for_pipe = 1;
		list->next->flag_for_pipe = -1;
		// list->flag_for_stdin = 2;
		// list->flag_for_stdout = 2;
		
		
		/* далее полученный лист отправляем в цикле на исполнение
        в зависимотсти какой флаг, лист будет отправяться в соответсвующую функцию
        во всех функциях создаетя дочерний процесс, который после исполнения будет завершаться
        на исполнение все листы, после создания дочернего процесса, отправляются в функцию ft_distributor 
        */ 
		
		current = list;
		while(current)
		{
			if (current->flag_for_pipe == 1 && !current->head_redirect)
			{
				printf("YOO\n");
				ft_pipe(path, current);
			}
			else if (current->head_redirect)
			{
				ft_redirections(current, path);
			}
			else if (!strcmp(current->cmd[0], "exit"))
				ft_exit(current);
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




/*
5 вариантов 


1) >
2) <             
3) > <
4) <<
5) << >






1) ls > 1 > 2 > 3
2) ls < 1 < 2 < 3
3) ls > 1 > 2 < 11 < 5
4) ls 1 < 4 < 5 << 3
5) ls > 4 < 1 < 3 << 11





1) ls > 3 < 1 >> 5 << 4 < 11
2) ls > 3 < 1 >> 5 << 4 < 11 << 6

> 3 > 4 

*/






int ft_chek_all_files(t_list *list)
{
	t_list *current;
	t_redirect *redent;
	int fd;
	current = list;
	while (current)
	{
		redent = list->head_redirect;
		while(redent)
		{
			if (redent->flag_for_stdout == 1)
			{	
				fd = open(redent->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					printf("Error: file not open\n");
					code_exit = 2;
					return (1);
				}
			}
			else if (redent->flag_for_stdout == 2)
			{
				fd = open(redent->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd == -1)
				{
					printf("Error: file not open\n");
					code_exit = 2;
					return(1);
				}
			}
			else if (redent->flag_for_stdin == 1)
			{
				fd = open(redent->filename, O_RDONLY, 0644);
				if (fd == -1)
				{
					printf("miniHELL: %s: No such file or directory\n", redent->filename);
					code_exit = 1;
					break;
				}
			}
			redent = redent->next;
		}
		current = current->next;
	}
	return (0);
}