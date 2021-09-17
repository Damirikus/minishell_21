#include "minishell.h"

// тут происходит распределение по командам на исполнение


int ft_realization(t_list *list, char **path, int len)
{
	int pid;

	if (list->flag_for_job == 1)
	{
		printf("miniHELL: %s: No such file or directory\n", list->filename_for_job);
		code_exit = 1;
		return (0);
	}
	if (!strcmp(list->cmd[0], "exit"))
		ft_exit(list, len);
//	else if (!strcmp(list->cmd[0], "export"))
//		ft_exit(list);
//	else if (!strcmp(list->cmd[0], "unset"))
//		ft_exit(list);
	else
	{
//		printf("cheeettttttt\n");
		pid = fork();
		if (pid == 0)
		{
			if (list->fd0 != -1)
				dup2(list->fd0, 0);
			if (list->fd1 != -1)
				dup2(list->fd1, 1);
			ft_distributor(path, list);
		}
		if (pid != 0)
		{
			wait(NULL);
		}
		if (list->fd0 != -1)
			close(list->fd0);
		if (list->fd1 != -1)
			close(list->fd1);
	}
	return (0);
}



int ft_distributor(char **path, t_list *list)
{
	char *full_path;

	full_path = ft_make_path(path, list);

	if (!strcmp(list->cmd[0], "echo"))
		ft_echo(full_path, list);
	else if (!strcmp(list->cmd[0], "pwd"))
		ft_pwd(full_path, list);
	else if (!strcmp(list->cmd[0], "cd"))
		ft_cd(full_path, list);
	else
	{
		if (execve(full_path, list->cmd, list->env) == -1)
		{
			printf("miniHELL: %s: command not found\n", list->cmd[0]);
			code_exit = 127;
			exit (127);
		}
	}
	exit(0);
		
}

void ft_pwd(char *full_path, t_list *list)
{
	char *str;
	int i;
	
	str = malloc(200);
    if (!str)
    {
        printf("memory allocation error\n");
        code_exit = 2;
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
    code_exit = 0;
	exit(0);
}

void ft_echo(char *full_path, t_list *list)
{
	int i;
	int count;
	int qw;

	count = 0;
	qw = 0;
	while (list->cmd[qw])
		qw++;
    if (qw == 1)
    {
        write(1, "\n", 1);
        code_exit = 0;
        exit(0);
    }
	if (strcmp(list->cmd[1], "-n"))
	{
		
		i = 1;
		while (list->cmd[i])
		{
			count = 0;
			while (list->cmd[i][count])
			{
				write(1, &list->cmd[i][count], 1);
				count++;
			}
			if (i != qw - 1)
			{
				write(1, " ", 1);
			}
			i++;
		}
		write(1, "\n", 1);
	}
	else
	{
		i = 2;
		while (list->cmd[i])
		{
			count = 0;
			while (list->cmd[i][count])
			{
				write(1, &list->cmd[i][count], 1);
				count++;
			}
			if (i != qw - 1)
			{
				write(1, " ", 1);
			}
			i++;
		}
	}
    code_exit = 0;
	exit(0);
}

void ft_cd(char *full_path, t_list *list)
{
	int i;
	char s[200];
	i = 0;
	while (list->cmd[i])
		i++;
	if (!list->cmd[1])
	{
		ft_find_home(list);
	}
	if (chdir(list->cmd[1]) != 0)
	{
		printf("miniHELL: cd: %s: no such file or directory\n", list->cmd[1]);
        code_exit = 1;
		exit(1);
	}
	else
	{
		// printf("%s\n", getcwd(s, 100));
        code_exit = 0;
        exit(0);
	}
}

int ft_find_home(t_list *list)
{
	return (0);
}


void ft_exit(t_list *list, int len)
{
	int i;
	long code;
	if (len == 1)
		printf("exit\n");
	i = 0;
	if (list->cmd[1])
	{
		if (list->cmd[1][0] == 45 || list->cmd[1][0] == 43)
			i++;
		while (list->cmd[1][i])
		{
			if (!ft_isdigit(list->cmd[1][i]))
			{
				printf("miniHELL: exit: %s: numeric argument required\n", list->cmd[1]);
				if (len == 1)
				exit(255);
				else
				return;
			}
			i++;
		}
		if (!ft_check_max_min(list->cmd[1]))
		{
			printf("miniHELL: exit: %s: numeric argument required\n", list->cmd[1]);
				if (len == 1)
			exit(255);
				else
					return;
		}
		code = ft_atoi(list->cmd[1]);
	}
	i = 0;
	while (list->cmd[i])
		i++;
	if (i > 2)
	{
		printf("miniHELL: exit: too many arguments\n");
		code_exit = 1;
		return ;
	}
	if (code < 0)
	{
		code *= -1;
		code %= 256;
		code = 256 - code;
		if (len == 1)
			exit(code);
		else
			return;
	}
	if (len == 1)
		exit(code % 256);
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



