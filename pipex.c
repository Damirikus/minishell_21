#include "minishell.h"

//функция получает path из окржуения и сплитом делит все пути и заполняет двумерный массив
// char **ft_path(char *str)
// {
// 	char **tmp;

// 	int i;
// 	tmp = ft_split(str, ':');
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		tmp[i] = ft_strjoin(tmp[i], "/");
// 		i++;
// 	}
// 	return (tmp);
// }

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
	tmp[i] = malloc(305);
	getcwd(tmp[i], 305);
	tmp[i] = ft_strjoin(tmp[i], "/");
	i++;
	tmp[i] = NULL;
	return (tmp);
}

//создаем полный путь исполняемого файлы для execve
char *ft_make_path(char **path, t_list *list)
{
	int i;
	int fd;
	char *tmp;

	if (list->cmd[0][0] == '/')
		return (list->cmd[0]);
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
		if (fd)
			close(fd);
		free(tmp);
		i++;
	}
	return (NULL);
}


