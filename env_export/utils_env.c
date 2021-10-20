/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:17:59 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/20 15:42:34 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_remaker(t_data *data)
{
	t_env	*tmp_pwd;

	tmp_pwd = data->head_env;
	while (tmp_pwd)
	{
		if (ft_strncmp(tmp_pwd->content, "PWD", ft_strlen_key("PWD")) == 0 && \
		ft_strlen_key(tmp_pwd->content) == ft_strlen("PWD"))
		{
			data->current_pwd = ft_cutstr(tmp_pwd->content, 0, -1);
			break ;
		}
		tmp_pwd = tmp_pwd->next;
	}
}

int	check_name_unset(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		data->code_exit = 1;
		return (1);
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '\0')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		data->code_exit = 1;
		return (1);
	}
	return (0);
}

int	check_name_export(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		data->code_exit = 1;
		return (1);
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] != '=' && str[i] != '\0')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		data->code_exit = 1;
		return (1);
	}
	return (0);
}

int	ft_strlen_key(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

char	*add_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen_g(str) + 3));
	if (!result)
		ft_error(8, NULL);
	while (str[i] != '\0' && str[i] != '=')
		result[j++] = str[i++];
	result[j++] = str[i++];
	result[j++] = '"';
	while (str[i] != '\0')
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j++] = '"';
	result[j] = '\0';
	return (result);
}
