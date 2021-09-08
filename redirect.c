#include "minishell.h"

int ft_stdout(char **path, t_list *list)
{
	int fd;
	int pid;

	if (list->flag_for_stdout == 1)
	{	
        fd = open(list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            printf("Error: file not open\n");
            code_exit = 2;
            exit(1);
        }
    }
	else if (list->flag_for_stdout == 2)
	{
        fd = open(list->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            printf("Error: file not open\n");
            code_exit = 2;
            exit(1);
        }
    }
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

	if (list->flag_for_stdin == 1)
	{
        fd = open(list->filename, O_RDONLY, 0644);
        if (fd == -1)
        {
            printf("Error: file not open\n");
            code_exit = 2;
            exit(1);
        }
    }
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 0);
		ft_distributor(path, list);
		close(fd);
	}
	if (pid != 0)
	{
		close(fd);
		wait(NULL);
		dup2(list->pid_mother, 0);
	}
	return (0);
}


int ft_stdin2(char **path, t_list *list)
{
    int fd[2];
	int pid;
    char *str;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
        while(1)
        {
            get_next_line(0, &str);
            if (!strcmp(str, list->filename))
            {
                free(str);
                exit(0);
            }   
            printf("%s\n", str);
            free(str);
        }
		close(fd[1]);
	}
	if (pid != 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(NULL);
        ft_empty(path, list);
        dup2(list->pid_mother, 0);
	}
	return (0);
}
