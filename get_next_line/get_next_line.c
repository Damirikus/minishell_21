/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:43:37 by rphoebe           #+#    #+#             */
/*   Updated: 2021/07/14 18:38:30 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#define BUFFER_SIZE 48

int	badr_hari(char **line, char **tmp, char **buf)
{
	free(*buf);
	*line = till_n(*tmp);
	*tmp = n_till(*tmp);
	return (1);
}

char	*join(char *s1, char *s2)
{
	char	*dd;
	int		i;
	int		j;
	int		sl1;
	int		sl2;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	sl1 = ft_strlen_g(s1);
	sl2 = ft_strlen_g(s2);
	dd = (char *)malloc(sizeof(char) * (sl1 + sl2 + 1));
	if (dd == NULL)
		return (NULL);
	while (++i < sl1)
		dd[i] = s1[i];
	while (j < sl2)
		dd[i++] = s2[j++];
	dd[i] = '\0';
	free(s1);
	return (dd);
}

int	check(int fd, char **buf, char **line)
{
	if (BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1 || \
	line == NULL)
	{
		return (1);
	}
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buf == NULL)
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char	*tmp;
	char		*buf;

	if (check(fd, &buf, line))
		return (-1);
	ret = 1;
	while ((ret || ft_strchr(tmp, '\n')))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		tmp = join(tmp, buf);
		if (ft_strchr(tmp, '\n') != NULL)
			return (badr_hari(line, &tmp, &buf));
	}
	free(buf);
	if (!tmp)
	{
		*line = ft_strdup("");
		return (0);
	}
	*line = tmp;
	tmp = NULL;
	return (0);
}
