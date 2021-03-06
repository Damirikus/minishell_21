#include "minishell.h"

void	ft_closer(t_list *list)
{
	if (list->fd0 != -1)
		close(list->fd0);
	if (list->fd1 != -1)
		close(list->fd1);
}

void	ft_realization_mother(t_list *list, t_data *data)
{
	if (data->len > 1 && !list->next && data->flat % 2 == 0)
		close(data->b[0]);
	else if (data->len > 1 && !list->next && data->flat % 2 == 1)
		close(data->a[0]);
	if (data->flat % 2 == 0 && list->flag_for_pipe == 1)
	{
		if (data->b[0])
			close(data->b[0]);
		close(data->a[1]);
	}
	else if (data->flat % 2 == 1 && list->flag_for_pipe == 1)
	{
		if (data->a[0])
			close(data->a[0]);
		close(data->b[1]);
	}
	ft_closer(list);
	data->flat++;
}

int	ft_realization_part(t_list *list, t_data *data)
{
	int	p[2];

	if (data->len > 1 && list->next)
	{
		pipe(p);
		close(p[1]);
		if (list->next->fd0 == -1)
			list->next->fd0 = p[0];
	}
	printf("minishell: %s: No such file or directory\n", list->filename_for_job);
	ft_closer(list);
	data->code_exit = 1;
	return (0);
}

void	ft_realization_daughter_part(t_list *list, t_data *data)
{
	if (data->flat == 0 && list->flag_for_pipe == 1)
	{
		close(data->a[0]);
		if (list->fd1 == -1)
			dup2(data->a[1], 1);
		close(data->a[1]);
	}
	else if (data->flat % 2 == 1 && list->flag_for_pipe == 1)
	{
		if (list->fd0 == -1)
			dup2(data->a[0], 0);
		close(data->a[0]);
		close(data->b[0]);
		if (list->fd1 == -1)
			dup2(data->b[1], 1);
		close(data->b[1]);
	}
	else if (data->flat % 2 == 0 && list->flag_for_pipe == 1)
		ft_realization_daughter_part2(list, data);
}

void	ft_realization_daughter_part2(t_list *list, t_data *data)
{
	if (list->fd0 == -1)
		dup2(data->b[0], 0);
	close(data->b[0]);
	close(data->a[0]);
	if (list->fd1 == -1)
		dup2(data->a[1], 1);
	close(data->a[1]);
}

void	ft_realization_daughter(t_list *list, t_data *data)
{
	if (list->fd0 != -1)
		dup2(list->fd0, 0);
	if (list->fd1 != -1)
		dup2(list->fd1, 1);
	if (!list->next && data->len > 1)
	{
		if (data->flat % 2 == 0)
		{
			if (list->fd0 == -1)
				dup2(data->b[0], 0);
			close(data->b[0]);
		}
		else
		{
			if (list->fd0 == -1)
				dup2(data->a[0], 0);
			close(data->a[0]);
		}
	}
	else
		ft_realization_daughter_part(list, data);
	ft_distributor(list, data);
}

int	ft_realization_part_last(t_list *list, t_data *data, int *flag)
{
	int	pid;

	pid = 0;
	if (!strcmp(list->cmd[0], "export") && list->cmd[1] != NULL)
		ft_export(data, list);
	else if (!strcmp(list->cmd[0], "unset"))
		ft_unset(data, list);
	else
	{
		if (data->flat % 2 == 0 && list->flag_for_pipe == 1)
			pipe(data->a);
		else if (data->flat % 2 == 1 && list->flag_for_pipe == 1)
			pipe(data->b);
		pid = fork();
		*flag = 1;
		if (pid == 0)
			ft_realization_daughter(list, data);
		if (pid != 0)
			ft_realization_mother(list, data);
	}
	return (pid);
}

int	ft_realization(t_list *list, t_data *data)
{
	int	pid;
	int	flag;

	flag = 0;
	if (list->flag_for_job == 1)
		return (ft_realization_part(list, data));
	if (list->cmd[0])
	{
		ft_check_bild_func(list, data);
		if (!strcmp(list->cmd[0], "exit"))
			ft_exit(list, data->len, data);
		else if (!strcmp(list->cmd[0], "cd"))
			ft_cd(list, data);
		else
			pid = ft_realization_part_last(list, data, &flag);
		if (flag == 1)
			return (pid);
		else
			return (-99);
	}
	else
		ft_closer(list);
	return (0);
}

void	ft_check_bild_func(t_list *list, t_data *data)
{
	int	p[2];

	if ((!strcmp(list->cmd[0], "exit") || !strcmp(list->cmd[0], "cd") \
		|| (!strcmp(list->cmd[0], "export") && list->cmd[1]) \
		|| !strcmp(list->cmd[0], "unset")) \
		&& (list->flag_for_pipe == 1 \
		&& data->len > 1 && list->flag_for_job == 0))
	{
		pipe(p);
		close(p[1]);
		if (list->next->fd0 == -1)
			list->next->fd0 = p[0];
	}
}

int	ft_distributor(t_list *list, t_data *data)
{
	char	*full_path;

	full_path = ft_make_path(data->path, list);
	if (!strcmp(list->cmd[0], "echo"))
		ft_echo(list);
	else if (!strcmp(list->cmd[0], "pwd"))
		ft_pwd();
	else if (!strcmp(list->cmd[0], "env"))
		print_2d_massive(data->current_env, list, data);
	else if (!strcmp(list->cmd[0], "export"))
		print_2d_massive(data->current_export, list, data);
	else
		ft_distributor_part(list, data, full_path);
	ft_closer(list);
	exit(0);
}

void	ft_distributor_part(t_list *list, t_data *data, char *full_path)
{
	if (execve(full_path, list->cmd, data->execve_env) == -1)
	{
		dup2(data->fd_mother, 1);
		close(data->fd_mother);
		if (list->cmd[0][0] == '/' || (list->cmd[0][0] == '.'
				&& list->cmd[0][1] == '/'))
			printf("minishell: %s: no such file or directory\n", list->cmd[0]);
		else
			printf("minishell: %s: command not found\n", list->cmd[0]);
		ft_closer(list);
		exit (127);
	}
}

void	ft_unset(t_data *data, t_list *list)
{
	int	i;
	int	code;
	int	flag;

	i = 1;
	code = 0;
	flag = 0;
	while (list->cmd[i])
	{
		code = check_name_unset(list->cmd[i], data);
		if (code && !flag)
			flag = 1;
		if (!code && data->head_command->next == NULL)
			unset_env(data, list->cmd[i]);
		if (!ft_strcmp("PATH", list->cmd[i]))
			ft_free_path(data);
		i++;
	}
	data->code_exit = flag;
}

void	ft_export(t_data *data, t_list *list)
{
	int	i;
	int	code;
	int	flag;

	i = 1;
	code = 0;
	flag = 0;
	while (list->cmd[i])
	{
		code = check_name_export(list->cmd[i], data);
		if (code && !flag)
			flag = 1;
		if (!code && data->head_command->next == NULL)
			export_env(data, list->cmd[i]);
		i++;
	}
	data->code_exit = flag;
}

void	ft_pwd(void)
{
	char	*str;
	int		i;

	str = malloc(200);
	if (!str)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	getcwd(str, 200);
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	free(str);
	exit(0);
}

void	ft_echo(t_list *list)
{
	int	qw;
	int	k;

	qw = 0;
	while (list->cmd[qw])
		qw++;
	if (qw == 1)
	{
		write(1, "\n", 1);
		exit(0);
	}
	k = 1;
	if (list->cmd[1])
		k = ft_echo_part_null(list, k, qw);
	if (k == 1)
		ft_echo_part(list, 1, qw);
	else
		ft_echo_part2(list, k, qw);
	exit(0);
}

int	ft_echo_part_null(t_list *list, int k, int qw)
{
	int	i;
	int	flag;

	while (k < qw)
	{
		if (list->cmd[k][0] != '-')
			break ;
		if (list->cmd[k][0] == '-' && !list->cmd[k][1])
			break ;
		i = 1;
		flag = 0;
		while (list->cmd[k][i])
		{
			if (list->cmd[k][i] != 'n')
			{
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag == 1)
			break ;
		k++;
	}
	return (k);
}

void	ft_echo_part(t_list *list, int i, int qw)
{
	int	count;

	while (list->cmd[i])
	{
		count = 0;
		while (list->cmd[i][count])
		{
			write(1, &list->cmd[i][count], 1);
			count++;
		}
		if (i != qw - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	ft_echo_part2(t_list *list, int i, int qw)
{
	int	count;

	while (list->cmd[i])
	{
		count = 0;
		while (list->cmd[i][count])
		{
			write(1, &list->cmd[i][count], 1);
			count++;
		}
		if (i != qw - 1)
			write(1, " ", 1);
		i++;
	}
}

int	ft_cd(t_list *list, t_data *data)
{
	int	i;

	if (data->a[0])
		close(data->a[0]);
	if (data->b[0])
		close(data->b[0]);
	i = 0;
	while (list->cmd[i])
		i++;
	if (!list->cmd[1] || list->cmd[1][0] == '~')
	{
		if (ft_find_home(list, data))
		{
			printf("minishell: cd: HOME not set\n");
			return (0);
		}
	}
	if (data->len > 1)
		return (ft_cd_part_last(list, data));
	if (chdir(list->cmd[1]) != 0)
		return (ft_cd_part(list, data));
	renew_pwd_oldpwd(data);
	data->code_exit = 0;
	return (0);
}

int	ft_cd_part_last(t_list *list, t_data *data)
{
	DIR	*str;

	if (list->fd1 != -1)
		close(list->fd1);
	str = opendir(list->cmd[1]);
	if (!str)
		return (ft_cd_part(list, data));
	closedir(str);
	return (1);
}

int	ft_cd_part(t_list *list, t_data *data)
{
	printf("minishell: cd: %s: no such file or directory\n", list->cmd[1]);
	data->code_exit = 1;
	return (0);
}

int	ft_find_home(t_list *list, t_data *data)
{
	int	i;
	int	fr;

	fr = 0;
	i = 0;
	while (data->current_env[i])
	{
		if (data->current_env[i][0] == 'H' && data->current_env[i][1] == 'O'
		&& data->current_env[i][2] == 'M'
		&& data->current_env[i][3] == 'E' && data->current_env[i][4] == '=')
		{
			fr = 1;
			if (!list->cmd[1])
				ft_find_home_part(list, data, i);
			else if (list->cmd[1][0] == '~')
				list->cmd[1] = ft_strjoin_cd(data->current_env[i] + 5,
						list->cmd[1] + 1);
		}
		i++;
	}
	if (fr == 0)
		return (1);
	return (0);
}

void	ft_find_home_part(t_list *list, t_data *data, int i)
{
	free(list->cmd[0]);
	free(list->cmd);
	list->cmd = malloc(sizeof(char *) * 3);
	list->cmd[2] = NULL;
	list->cmd[0] = malloc(sizeof(char) * 3);
	ft_strlcpy(list->cmd[0], "cd", 3);
	list->cmd[1] = ft_strjoin_cd(data->current_env[i] + 5, "");
}

void	ft_exit(t_list *list, int len, t_data *data)
{
	int		i;
	long	code;

	code = 0;
	if (len == 1)
		printf("exit\n");
	if (list->fd1 != -1 && len > 1)
		close(list->fd1);
	i = 0;
	if (list->cmd[1])
	{
		if (ft_exit_inner_part(list, i, len, data) == 1)
			return ;
		if (!ft_check_max_min(list->cmd[1]))
			ft_exit_part_inner(list, data, len);
		code = ft_atoi(list->cmd[1]);
	}
	ft_exit_part(code, list, len, data);
}

void	ft_exit_part_inner(t_list *list, t_data *data, int len)
{
	printf("minishell: exit: %s: numeric argument required\n",
		   list->cmd[1]);
	if (len == 1)
	{
		free_whole_project(data);
		exit(255);
	}
	else
		return ;
}

int	ft_exit_inner_part(t_list *list, int i, int len, t_data *data)
{
	if (list->cmd[1][0] == 45 || list->cmd[1][0] == 43)
		i++;
	while (list->cmd[1][i])
	{
		if (!ft_isdigit(list->cmd[1][i]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				list->cmd[1]);
			if (len == 1)
			{
				free_whole_project(data);
				exit(255);
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_exit_part(long code, t_list *list, int len, t_data *data)
{
	int	i;

	i = 0;
	while (list->cmd[i])
		i++;
	if (i > 2)
		return (ft_exit_part2(data));
	if (code < 0)
	{
		code *= -1;
		code %= 256;
		code = 256 - code;
		if (len == 1)
		{
			free_whole_project(data);
			exit(code);
		}
		else
			return (0);
	}
	return (ft_exit_exit(data, len, code));
}

int	ft_exit_exit(t_data *data, int len, long code)
{
	if (len == 1)
	{
		free_whole_project(data);
		exit(code % 256);
	}
	else
		return (0);
}

int	ft_exit_part2(t_data *data)
{
	printf("minishell: exit: too many arguments\n");
	data->code_exit = 1;
	return (0);
}

int	ft_check_max_min(char *str)
{
	char	*buf;
	int		i;

	i = 0;
	if (ft_strlen(str) < 19)
		return (1);
	if (str[i] == 45)
		i++;
	if (i == 1)
	{
		buf = "9223372036854775808";
		if (strcmp(buf, str + 1) < 0)
			return (0);
	}
	else
	{
		buf = "9223372036854775807";
		if (strcmp(buf, str) < 0)
			return (0);
	}
	return (1);
}
