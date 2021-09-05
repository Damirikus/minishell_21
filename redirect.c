#include "minishell.h"

int ft_stdout(char **path, t_list *list)
{
	int fd;
	int pid;

	// char *full_path;

	// full_path = ft_make_path(path, list);
	if (list->flag_for_stdout == 1)
		fd = open(list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (list->flag_for_stdout == 2)
		fd = open(list->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		ft_distributor(path, list);
		close(fd);
	}
	if (pid != 0)
	{
		close(fd);
		dup2(list->pid_mother, 0);
		wait(NULL);
	}
	return (0);
}



int ft_stdin(char **path, t_list *list)
{
	int fd;
	int pid;

	char *full_path;

	full_path = ft_make_path(path, list);
	if (list->flag_for_stdout == 1)
		fd = open(list->filename, O_RDONLY, 0644);
	
	pid = fork();
	if (pid == 0)
	{
		printf("here\n");
		dup2(fd, 0);
		ft_distributor(path, list);
		close(fd);
	}
	if (pid != 0)
	{
		close(fd);
		dup2(list->pid_mother, 0);
		wait(NULL);
	}
	return (0);
}


// int ft_nextstdout(char **path, t_list *list)
// {
// 	int pid;

// 	char *full_path;

// 	full_path = ft_make_path(path, list);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(full_path, list->cmd, list->env);
// 	}
// 	if (pid != 0)
// 	{
// 		wait(NULL);
// 	}
// 	return (0);
// }