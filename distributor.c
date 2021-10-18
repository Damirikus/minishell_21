#include "minishell.h" //jiestjkeeeeeeeeee

// тут происходит распределение по командам на исполнение cat << 6 << 7 > 8 >> 2 < 5 | wc -l | cat > 100

void	printjkee(t_data *data)
{
	printf("pwd: %s\noldpwd: %s\n", data->current_pwd, data->current_oldpwd);
}

void	printpath(t_data *data)
{
	int	i;

	i = -1;
	while (data->path[++i])
		printf("%d: %s\n", i, data->path[i]);
}

int ft_realization(t_list *list, t_data *data)
{
	int pid;
	int p[2];
	pid = 0;
	int flag;
	flag = 0;
	if (list->flag_for_job == 1)
	{
		if (data->len > 1 && list->next)
		{
			pipe(p);
			close(p[1]);
			if (list->next->fd0 == -1)
				list->next->fd0 = p[0];
		}
		printf("minishell: %s: No such file or directory\n", list->filename_for_job);
		if (list->fd0 != -1)
			close(list->fd0);
		if (list->fd1 != -1)
			close(list->fd1);
		data->code_exit = 1;
		return (0);
	}
	if (list->cmd[0])
	{
		if (!strcmp(list->cmd[0], "exit"))
			ft_exit(list, data->len, data);
			else if (!strcmp(list->cmd[0], "cd"))
				ft_cd(list, data);
			else if (!strcmp(list->cmd[0], "export") && list->cmd[1] != NULL)
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
				flag = 1;
				if (pid == 0)
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
					else if (data->flat == 0 && list->flag_for_pipe == 1)
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
					{
						if (list->fd0 == -1)
							dup2(data->b[0], 0);
						close(data->b[0]);
						close(data->a[0]);
						if (list->fd1 == -1)
							dup2(data->a[1], 1);
						close(data->a[1]);
					}
					ft_distributor(list, data);
				}
				if (pid != 0)
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
					if (list->fd0 != -1)
						close(list->fd0);
					if (list->fd1 != -1)
						close(list->fd1);
					data->flat++;
				}
			}
			if (flag == 1)
				return (pid);
			else
				return (-99);
	}
	return (0);
}

int ft_distributor(t_list *list, t_data *data)
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
	if (list->fd0 != -1)
		close(list->fd0);
	if (list->fd1 != -1)
		close(list->fd1);
	exit(0);
}

void ft_distributor_part(t_list *list, t_data *data, char *full_path)
{
	if (execve(full_path, list->cmd, data->execve_env) == -1)
	{
		dup2(data->fd_mother, 1);
		close(data->fd_mother);
		if (list->cmd[0][0] == '/' || (list->cmd[0][0] == '.' && list->cmd[0][1] == '/'))
			printf("minishell: %s: no such file or directory\n", list->cmd[0]);
		else
			printf("minishell: %s: command not found\n", list->cmd[0]);
		if (list->fd0 != -1)
			close(list->fd0);
		if (list->fd1 != -1)
			close(list->fd1);
		exit (127);
	}
}

void	ft_unset(t_data *data, t_list *list) // проверить возвращаемый код ошибки code_exit
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

void	ft_export(t_data *data, t_list *list) // Если приходит аргумент без '=', и до этого эта переменная существовала => не делать ничего
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

void ft_pwd(void)
{
	char *str;
	int i;
	
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

void ft_echo(t_list *list)
{
	int qw;
	int k;
	int i;
	int flag;

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
		while (k < qw)
		{
			if (list->cmd[k][0] != '-')
				break;
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
				break;
			k++;
		}
		if (k == 1)
			ft_echo_part(list, 1, qw);
		else
			ft_echo_part2(list, k, qw);
		exit(0);
}

void ft_echo_part(t_list *list, int i, int qw)
{
	int count;
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

void ft_echo_part2(t_list *list, int i, int qw)
{
	int count;
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

int ft_cd(t_list *list, t_data *data)
{
	int i;
	DIR *str;
	if (data->a[0])
		close(data->a[0]);
	if (data->b[0])
		close(data->b[0]);
	i = 0;
	while (list->cmd[i])
		i++;
	if (!list->cmd[1] || list->cmd[1][0] == '~')
	{
		if(ft_find_home(list, data))
		{
			printf("minishell: cd: HOME not set\n");
			return (0);
		}
	}
	if (data->len > 1)
	{
		if (list->fd1 != -1)
			close(list->fd1);
		str = opendir(list->cmd[1]);
		if (!str)
			return (ft_cd_part(list, data));
		closedir(str);
		return (1);
	}
	if (chdir(list->cmd[1]) != 0)
        return (ft_cd_part(list, data));
	renew_pwd_oldpwd(data);
	data->code_exit = 0;
	return (0);
}

int ft_cd_part(t_list *list, t_data *data)
{
	printf("minishell: cd: %s: no such file or directory\n", list->cmd[1]);
	data->code_exit = 1;
	return (0);
}

int ft_find_home(t_list *list, t_data *data)
{
	int i;
	int f;
	f = 0;
	i = 0;
	while (data->current_env[i])
	{
		if (data->current_env[i][0] == 'H' && data->current_env[i][1] == 'O' && data->current_env[i][2] == 'M'
		&& data->current_env[i][3] == 'E' && data->current_env[i][4] == '=')
		{
			f = 1;
			if (!list->cmd[1])
			{
				free(list->cmd[0]);
				free(list->cmd);
				list->cmd = malloc( sizeof(char *) * 3);
				list->cmd[2] = NULL;
				list->cmd[0] = malloc(sizeof(char) * 3);
				ft_strlcpy(list->cmd[0], "cd", 3);
				list->cmd[1] = ft_strjoin_cd(data->current_env[i] + 5, "");

			}
			else if (list->cmd[1][0] == '~')
				list->cmd[1] = ft_strjoin_cd(data->current_env[i] + 5, list->cmd[1] + 1);
		}
		i++;
	}
	if (f == 0)
		return (1);
	return (0);
}


void ft_exit(t_list *list, int len, t_data *data)
{
	int i;
	long code;

	code = 0;
	if (len == 1)
		printf("exit\n");
	if (list->fd1 != -1 && len > 1)
		close(list->fd1);
	i = 0;
	if (list->cmd[1])
	{
		if (ft_exit_inner_part(list, i, len, data) == 1)
			return;
		if (!ft_check_max_min(list->cmd[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", list->cmd[1]);
				if (len == 1)
				{
					free_whole_project(data);
					exit(255);
				}
				else
					return;
		}
		code = ft_atoi(list->cmd[1]);
	}
	ft_exit_part(code, list, len, data);
}

int ft_exit_inner_part(t_list *list, int i, int len, t_data *data)
{
	if (list->cmd[1][0] == 45 || list->cmd[1][0] == 43)
		i++;
	while (list->cmd[1][i])
	{
		if (!ft_isdigit(list->cmd[1][i]))
		{
			printf("minishell: exit: %s: numeric argument required\n", list->cmd[1]);
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

void ft_exit_part(long code, t_list *list, int len, t_data *data)
{
	int i;
	i = 0;
	while (list->cmd[i])
		i++;
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		data->code_exit = 1;
		return ;
	}
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
			return;
	}
	if (len == 1)
	{
		free_whole_project(data);
		exit(code % 256);
	}
	else
		return;
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



