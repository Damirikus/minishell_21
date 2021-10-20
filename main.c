/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:39:08 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/20 19:19:01 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_data	*inital_setting(int argc, char **argv, char **env)
{
	t_data	*tmp;

	(void)argc;
	(void)argv;
	tmp = malloc(sizeof(t_data));
	if (!tmp)
		ft_error(8, NULL);
	initial_env_maker(tmp, env);
	tmp->len = 0;
	tmp->code_exit = 0;
	tmp->pids = NULL;
	if (export_env_variable_present(tmp, "PATH"))
		tmp->path = ft_path(getenv("PATH"));
	return (tmp);
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
		if (data->pids != NULL)
			free(data->pids);
		if (input)
			free(input);
	}
	free_whole_project(data);
	free(data);
}
