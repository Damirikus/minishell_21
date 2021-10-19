/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_init_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:42:02 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 23:03:50 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_to_2D_massive_env_execve(t_data *shell)
{
	int		i;
	t_env	*tmp;

	if (shell->execve_env)
		free(shell->execve_env);
	shell->execve_env = malloc(sizeof(char *) \
	* (list_to_2D_massive_env_len(shell) + 1));
	i = 0;
	tmp = shell->head_env;
	while (tmp)
	{
		if (export_env_variable_strong(tmp->content))
		{
			shell->execve_env[i] = tmp->content;
			i++;
		}
		tmp = tmp->next;
	}
	shell->execve_env[i] = NULL;
}

void	list_to_2D_massive_env(t_data *shell)
{
	int		i;
	t_env	*tmp;

	if (shell->current_env)
		free(shell->current_env);
	shell->current_env = malloc(sizeof(char *) \
	 * (list_to_2D_massive_env_len(shell) + 1));
	i = 0;
	tmp = shell->head_env;
	while (tmp)
	{
		if (export_env_variable_strong(tmp->content))
		{
			shell->current_env[i] = tmp->content;
			i++;
		}
		tmp = tmp->next;
	}
	shell->current_env[i] = NULL;
}

void	list_to_2D_massive_export_helper(t_data *shell)
{
	int		i;
	t_env	*tmp;
	char	*str;
	int		j;

	i = -1;
	j = 0;
	tmp = shell->head_env;
	while (++i < ft_lstsize_env(shell->head_env))
	{
		if (!(tmp->content[0] == '_' && tmp->content[1] == '='))
		{
			str = add_quotes(tmp->content);
			shell->current_export[j] = ft_strjoin_export("declare -x ", str);
			free(str);
			j++;
		}
		tmp = tmp->next;
	}
	shell->current_export[j] = NULL;
}

void	list_to_2D_massive_export(t_data *shell)
{
	if (shell->current_export)
		ft_free_for_export(shell);
	shell->current_export = malloc(sizeof(char *) \
	* (ft_lstsize_env(shell->head_env) + 1));
	if (!shell->current_export)
		ft_error(8, NULL);
	list_to_2D_massive_export_helper(shell);
	list_to_2D_massive_export_sort_sys(shell);
}

void	env_to_list(t_data *shell)
{
	int	i;

	i = -1;
	while (shell->original_env[++i])
		ft_lstadd_back_env(&shell->head_env, \
		ft_lstnew_initial_env(shell->original_env[i]));
	list_to_2D_massive_env(shell);
	list_to_2D_massive_export(shell);
	list_to_2D_massive_env_execve(shell);
}
