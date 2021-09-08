#include "minishell.h"

char **ft_path(char *str)
{
	char **tmp;
	int i;
	tmp = ft_split(str, ':');
	i = 0;
	while (tmp[i])
	{
		tmp[i] = ft_strjoin(tmp[i], "/");
		i++;
	}
	return (tmp);
}


int ft_pipe(char **path, t_list *list)
{
	int fd[2];
	int pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		ft_distributor(path, list);
		close(fd[1]);
	}
	if (pid != 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(NULL);
	}
	return (0);
}

char *ft_make_path(char **path, t_list *list)
{
	int i;
	int fd;
	char *tmp;
	
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], list->cmd[0]);
		fd = open(tmp, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}




/*
 *
 *
 *
pipe(fd[2]);
fd[1] = в который пишем
fd[0] = из которого читаем



 в начале сохраним нулевой пид родительского процесса

 int pid_0 = dup(0);



Если встретил пайп(flag == 1)

 pid = fork();
 if (pid == 0)
 {
 	dup2(fd[1], 1);
 	close(fd[0]);
 	execve("/bin/ls", ... , ...);
 	close(fd[1]);
 }
 if (pid != 0)
 {
 	dup2(fd[0], 0);
 	close(fd[1]);
 	wait(..);
 }

else
 execve("/bin/grep", ... , ...);
 dup2(pid_0, 0);

*/
