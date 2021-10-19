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
	data->path = NULL;
	data->fd_mother = dup(1);
	data->sg = rl_getc_function;
	env_to_list(data);
	pwd_oldpwd_remaker(data);
	shlvl_plus(data);
}

void	ft_hz(int sig)
{
	(void)sig;
	printf("Quit: 3\n");
}

t_data	*inital_setting(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_data	*tmp;

	tmp = malloc(sizeof(t_data));
	initial_env_maker(tmp, env);
	tmp->len = 0;
	tmp->code_exit = 0;
	if (export_env_variable_present(tmp, "PATH"))
		tmp->path = ft_path(getenv("PATH"));
	return (tmp);
}

void	initial_loop_setting(t_data *data)
{
	f = 0;
	if (data->td[0])
		close(data->td[0]);
	if (data->td[1])
		close(data->td[1]);
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	rl_getc_function = data->sg;
}

void	main_helper(t_data *data)
{
	int		i;
	int		status;
	t_list	*current;
	int		pid;

	data->flat = 0;
	current = data->head_command;
	while (current)
	{
		pid = ft_realization(current, data);
		current = current->next;
	}
	i = 0;
	if (pid != -99)
	{
		while (i < data->len)
		{
			if (waitpid(pid, &status, 0) != pid)
				status = -1;
			if (status != -1)
				data->code_exit = status / 256;
			i++;
		}
	}
}

void	main_sleep_and_close(t_data *data)
{
	main_helper(data);
	usleep(10000);
	if (data->td[0])
		close(data->td[0]);
	if (data->td[1])
		close(data->td[1]);
}

void	signals_and_add_history(char *input, t_data *data)
{
	if (*input)
		add_history(input);
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, ft_hz);
	rl_getc_function = data->sg;
}

int	preparation_main(char *input, t_data *data)
{
	t_list	*current;

	if (!preparser(input, data))
	{
		data->head_command = parser(input, data);
		data->len = ft_chek_all_files(data->head_command, data);
		if (data->len == -1)
		{
			current = data->head_command;
			while (current)
			{
				ft_closer(current);
				current = current->next;
			}
			free(input);
			return (1);
		}
		main_sleep_and_close(data);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	data = inital_setting(argc, argv, env);
	while (1)
	{
		initial_loop_setting(data);
		input = readline("minishell %> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		signals_and_add_history(input, data);
		if (preparation_main(input, data))
			continue ;
		list_free(&data->head_command);
		free(input);
	}
	free_whole_project(data);
	free(data);
}

void	ft_ctrlc(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_ctrl(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}
