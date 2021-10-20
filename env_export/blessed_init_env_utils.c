/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_init_env_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:55:51 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/20 15:48:21 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_to_2d_massive_export_sort_sys(t_data *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (shell->current_export[i])
	{
		if (shell->current_export[i + 1] != NULL)
		{
			if (ft_strcmp(shell->current_export[i], \
			shell->current_export[i + 1]) == 1)
			{
				tmp = shell->current_export[i];
				shell->current_export[i] = shell->current_export[i + 1];
				shell->current_export[i + 1] = tmp;
				i = -1;
			}
		}
		i++;
	}
}

void	print_2d_massive(char **mass, t_list *list, t_data *data)
{
	int	i;

	(void)list;
	i = -1;
	while (mass[++i])
	{
		ft_putstr_fd(mass[i], 1);
		write(1, "\n", 1);
	}
	data->code_exit = 0;
}

int	list_to_2d_massive_env_len(t_data *shell)
{
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = shell->head_env;
	while (tmp)
	{
		if (export_env_variable_strong(tmp->content))
			len++;
		tmp = tmp->next;
	}
	return (len);
}

void	ft_free_for_export(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->current_export[i])
	{
		free(shell->current_export[i]);
		i++;
	}
	free(shell->current_export);
}
