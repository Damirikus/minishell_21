/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_append_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:17:55 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/19 23:30:20 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_env_variable_present(t_data *shell, char *str)
{
	t_env	*tmp;

	tmp = shell->head_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, ft_strlen_key(str)) == 0 && \
		ft_strlen_key(tmp->content) == ft_strlen_key(str))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	export_env_variable_strong(char *string)
{
	int	i;

	i = 0;
	while (ft_isalnum(string[i]) || string[i] == '_')
		i++;
	if (string[i] == '+')
		i++;
	if (string[i] == '=')
		return (1);
	return (0);
}

char	*clean_string_export(char *string)
{
	int		i;
	int		j;
	int		flag;
	char	*result;

	i = 0;
	j = 0;
	flag = 0;
	result = malloc(sizeof(char) * ft_strlen(string));
	if (!result)
		ft_error(8, NULL);
	while (string[i] != '\0' && string[i] != '+')
		result[j++] = string[i++];
	i++;
	while (string[i])
	{
		result[j] = string[i];
		i++;
		j++;
	}
	result[j] = 0;
	return (result);
}

t_env	*export_env_append_tmp(t_data *shell, char *clean_string)
{
	t_env	*tmp;

	tmp = shell->head_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, clean_string, \
		ft_strlen_key(clean_string)) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	export_env_append(t_data *shell, char *string)
{
	char	*clean_string;
	t_env	*tmp;

	clean_string = clean_string_export(string);
	if (!export_env_variable_present(shell, clean_string))
	{
		ft_lstadd_back_env(&shell->head_env, \
		ft_lstnew_initial_env(clean_string));
		free(clean_string);
		return ;
	}
	tmp = export_env_append_tmp(shell, clean_string);
	if (tmp)
	{
		if (!export_env_variable_strong(tmp->content))
			tmp->content = ft_strjoin_pars(tmp->content, "=");
	}
	tmp->content = ft_strjoin_pars(tmp->content, clean_string \
	+ ft_strlen_key(clean_string) + 1);
	free(clean_string);
	renew_env_export_massive(shell);
}
