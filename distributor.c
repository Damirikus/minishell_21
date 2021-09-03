#include "minishell.h"

int ft_distributor(char **path, t_list *list)
{
	char *full_path;

	full_path = ft_make_path(path, list);
	if (!strcmp(list->cmd[0], "echo"))
		ft_echo(full_path, list);
	if (!strcmp(list->cmd[0], "pwd"))
		ft_pwd(full_path, list);
	else
	{
		execve(full_path, list->cmd, list->env);
	}
	exit(0);
		
}

void ft_pwd(char *full_path, t_list *list)
{
	char *str;
	int i;
	
	str = malloc(200);
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

void ft_echo(char *full_path, t_list *list)
{
	int i;
	int count;
	int qw;
	count = 0;
	qw = 0;
	while (list->cmd[qw])
		qw++;
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
	// i = 1;
	// while (list->cmd[i])
	// {
	// 	printf("%s\n", list->cmd[i]);
	// 	write(1, " ", 1);
	// 	i++;
	// }
	exit(0);
}