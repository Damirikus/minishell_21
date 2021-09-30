#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char* input;
	t_data *data;
	data = malloc(sizeof(t_data));
	data->head_command = NULL;
	data->len = 0;
	data->current_env = NULL;
	data->current_export = NULL;
	data->original_env = NULL;
	data->head_env = NULL;
	t_list *current;
	data->path = ft_path(getenv("PATH"));

	t_list *tmp;

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
			data->head_command = parser(input, env);
			tmp = data->head_command;
			while (tmp)
			{
				tmp->env = env;
				tmp = tmp->next;
			}

			ft_print_all(data);

			//на этом тапе происходит проверка всех файлов и их создание, если листов несколько, то есть пайпы
			data->len = ft_chek_all_files(data->head_command);
			current = data->head_command;
			while (current)
			{
				if (current->cmd[0])
					ft_realization(current, data);
				current = current->next;
			}
		}

		/* do stuff */

		// Т. к. вызов readline() выделяет память, но не освобождает (а возвращает), то эту память нужно вернуть (освободить).
		list_free(&data->head_command);
		free(input);

	}
}



void ft_print_all(t_data *data)
{
	int i;
	i = 0;
	// while (data->path[i])
	// {
	// 	printf("path[%d] = %s\n", i, data->path[i]);
	// 	i++;
	// }
	printf("\n");
	i = 0;
	t_list *tmp;
	tmp = data->head_command;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			printf("CMD[%d] = %s\n", i, tmp->cmd[i]);
			i++;
		}
		printf("______________\n");
		tmp = tmp->next;
	}
}

