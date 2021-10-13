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

char	**ft_path_2(char **tmp, int size)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (size + 1));
	result[i] = malloc(305);
	getcwd(result[i], 305);
	result[i] = ft_strjoin(result[i], "/");
	i++;
	while (tmp[j])
	{
		result[i] = ft_strdup(tmp[j]);
		free(tmp[j]);
		i++;
		j++;
	}
	free(tmp);
	result[i] = NULL;
	return (result);
}

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
	// return (ft_path_2(tmp, i));
	return (tmp);
}

char	*try_current_dir(char *filename)
{
	char	*dir;
	int		fd;

	dir = malloc(305);
	getcwd(dir, 305);
	dir = ft_strjoin(dir, "/");
	dir = ft_strjoin(dir, filename);
	fd = open(dir, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		return (dir);
	}
	if (fd)
		close(fd);
	free(dir);
	return (NULL);
}

//создаем полный путь исполняемого файлы для execve
char *ft_make_path(char **path, t_list *list) //jiest
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
	return (try_current_dir(list->cmd[0]));
}


