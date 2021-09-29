#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char* input;
	t_data data;
	t_list *current;
	data.path = ft_path(getenv("PATH"));

	char *cmdd[] = {"exit", NULL};
//	char shell_prompt[100];
	data.head_command = ft_lstnew(cmdd, env);

	while(1)
	{
//		signal(SIGINT, ft_ctrlc);
//		signal(SIGQUIT, ft_ctrlq);
//		signal(SIGQUIT, ft_ctrld);


//		snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));
		input = readline("miniHELL %> ");
		if (!input)
			break;
		rl_bind_key('\t', rl_complete);
		add_history(input);


        //на этом этапе происходит парс, на выходе лист со всеми командами
		//  list = ft_pars(input);
		if (!preparser(input))
		{
			data.head_command = parser(input, env);

			//на этом тапе происходит проверка всех файлов и их создание, если листов несколько, то есть пайпы
			data.len = ft_chek_all_files(data.head_command);
			current = data.head_command;
			while (current)
			{
				ft_realization(current, data.path, data.len);
				current = current->next;
			}
		}



		/* do stuff */

		// Т. к. вызов readline() выделяет память, но не освобождает (а возвращает), то эту память нужно вернуть (освободить).
		free(input);

	}
}


