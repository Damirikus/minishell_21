/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b-ins_pwd_export_unset.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:53:40 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/21 14:35:50 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_key_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (i != 0 && str[i - 1] == '+')
		i--;
	return (i);
}

void	ft_unset(t_data *data, t_list *list)
{
	int	i;
	int	code;
	int	flag;

	i = 1;
	code = 0;
	flag = 0;
	while (list->cmd[i])
	{
		code = check_name_unset(list->cmd[i], data);
		if (code && !flag)
			flag = 1;
		if (!code && data->head_command->next == NULL)
			unset_env(data, list->cmd[i]);
		if (!ft_strcmp("PATH", list->cmd[i]))
			ft_free_path(data);
		i++;
	}
	data->code_exit = flag;
}

void	ft_export(t_data *data, t_list *list)
{
	int	i;
	int	code;
	int	flag;

	i = 1;
	code = 0;
	flag = 0;
	while (list->cmd[i])
	{
		code = check_name_export(list->cmd[i], data);
		if (code && !flag)
			flag = 1;
		if (!code && data->head_command->next == NULL)
			export_env(data, list->cmd[i]);
		if ((!ft_strncmp("PATH", list->cmd[i], 4) || \
		!ft_strncmp("PATH+", list->cmd[i], 5)) \
		&& ft_strlen_key_export(list->cmd[i]) \
		== 4 && export_env_variable_strong(list->cmd[i]) && \
		!data->head_command->next && !code)
			remake_path(data);
		i++;
	}
	data->code_exit = flag;
}

void	ft_pwd(void)
{
	char	*str;
	int		i;

	str = malloc(200);
	if (!str)
	{
		printf("Memory allocation error\n");
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
	exit(0);
}
