#include "minishell.h"

void	initial_env_maker(t_data *data, char **env)
{
	data->head_command = NULL;
	data->current_env = NULL;
	data->current_export = NULL;
	data->original_env = env;
	data->head_env = NULL;
	data->current_pwd = NULL;
	data->current_oldpwd = NULL;
	env_to_list(data);
	// pwd_oldpwd_remaker(data);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char* input;
	t_data *data;
	data = malloc(sizeof(t_data));
	initial_env_maker(data, env);
	t_list *current;
	data->len = 0;
	data->path = ft_path(getenv("PATH"));

	t_list *tmp;
	while(1)
	{
//		signal(SIGINT, ft_ctrlc);
		signal(SIGQUIT, SIG_IGN);
//		signal(SIGQUIT, ft_ctrld);


//		snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));
		input = readline("minishell %> ");
		if (!input)
			break;
		rl_bind_key('\t', rl_complete);
		add_history(input);


        //на этом этапе происходит парс, на выходе лист со всеми командами
		//  list = ft_pars(input);
		if (!preparser(input))
		{
			data->head_command = parser(input, data->current_env);
			tmp = data->head_command;
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
//	i = 0;
//	while (data->path[i])
//	{
//		printf("path[%d] = %s\n", i, data->path[i]);
//		i++;
//	}
//	printf("\n");
//	i = 0;
	t_list *tmp;
	t_redirect *red;
	tmp = data->head_command;
	while (tmp)
	{
		red = tmp->head_redirect;
		i = 0;
		while (tmp->cmd[i])
		{
			printf("CMD[%d] = %s\n", i, tmp->cmd[i]);
			i++;
		}
		printf("_____________________\n");
		printf("flag_for_pipe = %d\n", tmp->flag_for_pipe);
		printf("_____________________\n");
		while (red)
		{
			printf("REDIRECTS\n");
			printf("stdin = %d\n", red->flag_for_stdin);
			printf("stdout = %d\n", red->flag_for_stdout);
			red = red->next;
		}
		printf("______________________________________________________________\n");
		tmp = tmp->next;
	}
}

//void ft_ctrlc(int signal)
//{
//	(void)signal;
//	printf("\n");
//	rl_on_new_line();
//	rl_replace_line("", 0);
//	rl_redisplay();
//}
