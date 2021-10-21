/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:02:48 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/21 15:24:41 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_list *list, t_data *data)
{
	int	i;

	if (data->a[0])
		close(data->a[0]);
	if (data->b[0])
		close(data->b[0]);
	i = 0;
	while (list->cmd[i])
		i++;
	if (!list->cmd[1] || list->cmd[1][0] == '~')
	{
		if (ft_find_home(list, data))
		{
			printf("minishell: cd: HOME not set\n");
			return (0);
		}
	}
	if (data->len > 1)
		return (ft_cd_part_last(list, data));
	if (chdir(list->cmd[1]) != 0)
		return (ft_cd_part(list, data));
	renew_pwd_oldpwd(data);
	data->code_exit = 0;
	return (0);
}

int	ft_cd_part_last(t_list *list, t_data *data)
{
	DIR	*str;

	if (list->fd1 != -1)
		close(list->fd1);
	str = opendir(list->cmd[1]);
	if (!str)
		return (ft_cd_part(list, data));
	closedir(str);
	return (1);
}

int	ft_cd_part(t_list *list, t_data *data)
{
	printf("minishell: cd: %s: no such file or directory\n", list->cmd[1]);
	data->code_exit = 1;
	return (0);
}

int	ft_find_home(t_list *list, t_data *data)
{
	int	i;
	int	fr;

	fr = 0;
	i = 0;
	while (data->current_env[i])
	{
		if (data->current_env[i][0] == 'H' && data->current_env[i][1] == 'O'
		&& data->current_env[i][2] == 'M'
		&& data->current_env[i][3] == 'E' && data->current_env[i][4] == '=')
		{
			fr = 1;
			if (!list->cmd[1])
				ft_find_home_part(list, data, i);
			else if (list->cmd[1][0] == '~')
				list->cmd[1] = ft_strjoin_cd(data->current_env[i] + 5,
						list->cmd[1] + 1);
		}
		i++;
	}
	if (fr == 0)
		return (1);
	return (0);
}

void	ft_find_home_part(t_list *list, t_data *data, int i)
{
	free(list->cmd[0]);
	free(list->cmd);
	list->cmd = malloc(sizeof(char *) * 3);
	if (!list->cmd)
		ft_error(8, NULL);
	list->cmd[2] = NULL;
	list->cmd[0] = malloc(sizeof(char) * 3);
	if (!list->cmd[0])
		ft_error(8, NULL);
	ft_strlcpy(list->cmd[0], "cd", 3);
	list->cmd[1] = ft_strjoin_cd(data->current_env[i] + 5, "");
}
