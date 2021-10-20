/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:40:35 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/20 22:20:52 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remake_path(t_data *data)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = data->head_env;
	ft_free_path(data);
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PATH", ft_strlen_key(tmp->content)) \
		== 0 && ft_strlen_key(tmp->content) == 4)
			break ;
		tmp = tmp->next;
	}
	data->path = ft_split(tmp->content + 5, ':');
	while (data->path[i])
	{
		data->path[i] = ft_strjoin(data->path[i], "/");
		i++;
	}
	data->path[i] = NULL;
}

char	**ft_path(char *str)
{
	char	**tmp;
	int		i;

	tmp = ft_split(str, ':');
	i = 0;
	while (tmp[i])
	{
		tmp[i] = ft_strjoin(tmp[i], "/");
		i++;
	}
	tmp[i] = malloc(305);
	if (!tmp[i])
		ft_error(8, NULL);
	getcwd(tmp[i], 305);
	tmp[i] = ft_strjoin(tmp[i], "/");
	i++;
	tmp[i] = NULL;
	return (tmp);
}

char	*try_current_dir(char *filename)
{
	char	*dir;
	int		fd;

	dir = malloc(305);
	if (!dir)
		ft_error(8, NULL);
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

char	*ft_make_path(char **path, t_list *list)
{
	int		i;
	int		fd;
	char	*tmp;

	if (list->cmd[0][0] == '/')
		return (list->cmd[0]);
	i = 0;
	if (path)
	{
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
	}
	return (try_current_dir(list->cmd[0]));
}
