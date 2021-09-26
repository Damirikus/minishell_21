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
	int len;

	
	char *cmdd[] = {NULL};
	// char *cmdd2[] = {"pwd", NULL};
	// char *cmdd2[] = {"wc", "-l", NULL};
	// char *cmdd[] = {NULL};

	list = ft_lstnew(cmdd, env);
	// new = ft_lstnew(cmdd2, env);
	// list->next = new;
	// ff = ft_lstnew(cmdd3, env);
	// list->filename = str;
	// list->next = ff;
//	list->head_redirect = ft_lstnew_redirect();
//	list->head_redirect->filename = "1";
//	list->head_redirect->flag = 1;
//	list->head_redirect->flag_for_stdin = 2;
//
//	 t_redirect *one;
//	 one = ft_lstnew_redirect();
//	 one->filename = "2";
//	 one->flag = 1;
//	 one->flag_for_stdout = 1;
//	 list->head_redirect->next = one;

//	t_redirect *on;
//	on = ft_lstnew_redirect();
//	on->filename = "3";
//	on->flag = 1;
//	on->flag_for_stdout = 2;
//	list->head_redirect->next->next = on;


//	list->flag_for_pipe = 1;



//	char *cmdd2[] = {"wc","-l",  NULL};
// char *cmdd2[] = {"pwd", NULL};
 // char *cmdd2[] = {"wc", "-l", NULL};
 // char *cmdd[] = {NULL};

//	 list = ft_lstnew(cmdd, env);
//	new = ft_lstnew(cmdd2, env);
//	list->next = new;
 // ff = ft_lstnew(cmdd3, env);1
//	// // list->filename = str;
//	// // list->next = ff;
//	list->next->head_redirect = ft_lstnew_redirect();
//	list->next->head_redirect->filename = "4";
//	 list->next->head_redirect->flag = 1;
//	list->next->head_redirect->flag_for_stdin = 2;
//
//	t_redirect *on;
//	on = ft_lstnew_redirect();
//	on->filename = "2";
//	// one->flag_for_stdin = 1;
//	on->flag = 1;
//	on->flag_for_stdin = 1;
//	list->next->head_redirect->next = on;
	
//	list->next->flag_for_pipe = 1;
	
//	char *cmdd3[] = {"cat",  NULL};
//	// // char *cmdd2[] = {"pwd", NULL};
//	// // char *cmdd2[] = {"wc", "-l", NULL};
//	// // char *str = "1";
//	// // char *cmdd[] = {NULL};
//
//	// // list = ft_lstnew(cmdd, env);
//	// new = ft_lstnew(cmdd2, env);
//	// list->next = new;
//	ff = ft_lstnew(cmdd3, env);
//	list->next->next = ff;
//	list->next->next->head_redirect = ft_lstnew_redirect();
//	list->next->next->head_redirect->filename = "5";
//	list->next->next->head_redirect->flag = 1;
//	list->next->next->head_redirect->flag_for_stdout = 1;
//
//	t_redirect *o;
//	o = ft_lstnew_redirect();
//	o->filename = "3";
//	// // one->flag_for_stdin = 1;
//	o->flag = 1;
//	o->flag_for_stdout = 1;
//	list->next->next->head_redirect->next = on;

	char **path;
	path = ft_path(getenv("PATH"));


//	char shell_prompt[100];



	while(1)
	{
//		signal(SIGINT, ft_ctrlc);
//		signal(SIGQUIT, ft_ctrlq);
//		signal(SIGQUIT, ft_ctrld);


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
		

		//на этом тапе происходит проверка всех файлов и их создание, если листов несколько, то есть пайпы
		len = ft_chek_all_files(list);
		current = list;
		while (current)
		{
			ft_realization(current, path, len);
			current = current->next;
		}


		/* do stuff */

		// Т. к. вызов readline() выделяет память, но не освобождает (а возвращает), то эту память нужно вернуть (освободить).
		free(input);

	}
}


