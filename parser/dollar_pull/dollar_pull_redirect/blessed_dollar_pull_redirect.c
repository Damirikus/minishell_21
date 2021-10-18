/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_dollar_pull_redirect.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:37:19 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 20:39:05 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	dollar_pull_exit_code_redirect(char **str, int start, t_data *data)
{
	char	*result;
	char	*tmp;
	char	*exit_code_str;
	int		i;
	int		j;

	exit_code_str = ft_itoa(data->code_exit);
	tmp = *str;
	result = malloc(sizeof(char) * (ft_strlen(tmp) - \
	2 + ft_strlen(exit_code_str) + 1));
	i = -1;
	j = -1;
	while (++i < start)
		result[i] = tmp[i];
	while (exit_code_str[++j])
		result[i++] = exit_code_str[j];
	start += 1;
	while (tmp[++start])
		result[i++] = tmp[start];
	result[i] = 0;
	free(*str);
	*str = result;
	free(exit_code_str);
}

void	dollar_pull_helper_redirect(char **str, int j, t_data *data)
{
	int		start;
	char	*value;
	char	*tmp;

	start = j + 1;
	value = NULL;
	j++;
	tmp = *str;
	if (tmp[start] == '?')
	{
		dollar_pull_exit_code_redirect(str, j - 1, data);
		return ;
	}
	value = dollar_pull_helper_value_maker_redirect(tmp, start, &j, data);
	if (value != NULL)
		dollar_pull_swaper_redirect(str, value, start);
	else
		dollar_cut_from_str_redirect(str, start - 1, j - 1);
}

void	dollar_pull_special_skip_redirect(char **str, int *j, t_data *data)
{
	char	*tmp;

	tmp = *str;
	*j = *j + 1;
	while (tmp[*j] != '\"' && tmp[*j] != '\0')
	{
		if (tmp[*j] == '$' && (ft_isalnum_strong(tmp[*j + 1], 2)))
		{
			dollar_pull_helper_redirect(str, *j, data);
			*j = -1;
			return ;
		}
		*j = *j + 1;
	}
	*j = *j + 1;
}

void	dollar_pull_redirect(t_redirect *tmp, t_data *data)
{
	int			j;

	j = 0;
	while (tmp->filename[j])
	{
		if (j != -1 && tmp->filename[j] == '\"')
			dollar_pull_special_skip_redirect(&tmp->filename, &j, data);
		if (j != -1 && tmp->filename[j] == '\'')
			ft_skip_quotes(tmp->filename, &j);
		if (j != -1 && tmp->filename[j] == '$' \
		&& (ft_isalnum_strong(tmp->filename[j + 1], 1)))
		{
			dollar_pull_helper_redirect(&tmp->filename, j, data);
			j = -1;
		}
		if (j == -1 || (tmp->filename[j] != '\'' \
		&& tmp->filename[j] != '\0'))
			j++;
	}
}

void	dollar_pull_for_redirect(t_list *head_command, t_data *data)
{
	t_list		*tmp;
	t_redirect	*tmp_redirect;

	tmp = head_command;
	while (tmp)
	{
		tmp_redirect = tmp->head_redirect;
		while (tmp_redirect)
		{
			dollar_pull_redirect(tmp_redirect, data);
			tmp_redirect = tmp_redirect->next;
		}
		tmp = tmp->next;
	}
}
