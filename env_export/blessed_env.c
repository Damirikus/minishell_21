/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:41:57 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/20 15:46:28 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	renew_env_export_massive(t_data *shell)
{
	list_to_2d_massive_env(shell);
	list_to_2d_massive_export(shell);
}

void	unset_env(t_data *shell, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = shell->head_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, key, ft_strlen_key(tmp->content)) == 0 \
		&& ft_strlen_key(tmp->content) == ft_strlen_key(key))
		{
			if (ft_strcmp(tmp->content, shell->head_env->content) == 0)
			{
				shell->head_env = shell->head_env->next;
				free(tmp->content);
				free(tmp);
				break ;
			}
			prev->next = tmp->next;
			free(tmp->content);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	renew_env_export_massive(shell);
}

void	export_env(t_data *shell, char *string)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_key(string);
	while (i < len)
	{
		if (string[i] == '+')
		{
			export_env_append(shell, string);
			renew_env_export_massive(shell);
			return ;
		}
		i++;
	}
	if (export_env_variable_present(shell, string) \
	&& !export_env_variable_strong(string))
		return ;
	if (export_env_variable_present(shell, string) \
	&& export_env_variable_strong(string))
		unset_env(shell, string);
	ft_lstadd_back_env(&shell->head_env, ft_lstnew_initial_env(string));
	renew_env_export_massive(shell);
}
