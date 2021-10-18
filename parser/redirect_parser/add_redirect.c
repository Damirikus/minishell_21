/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:53:01 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 19:50:22 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_redirect_flag(char *str, int *j, int *flag)
{
	if (str[*j - 1] == '<' && str[*j] == '>')
	{
		*flag = 5;
		*j = *j + 1;
	}
	else if (str[*j] == '>')
	{
		*flag = 2;
		*j = *j + 1;
	}
	else if (str[*j] == '<')
	{
		*flag = 4;
		*j = *j + 1;
	}
	else if (str[*j] != '>' && str[*j] != '<' && str[*j - 1] == '>')
		*flag = 1;
	else if (str[*j] != '>' && str[*j] != '<' && str[*j - 1] == '<')
		*flag = 3;
}

void	add_redirect(char *str, t_list *tmp, int *i)
{
	int	j;
	int	flag;
	int	start;

	j = *i + 1;
	add_redirect_flag(str, &j, &flag);
	while (str[j] != '\0' && str[j] < 33)
		j++;
	start = j;
	while (str[j] != '\0' && str[j] != '>' && str[j] != '<' && str[j] > 32)
	{
		if (str[j] == '\'' || str[j] == '\"')
			ft_skip_quotes(str, &j);
		if (str[j] != '\'' && str[j] != '\"' && str[j] != '>' && \
		str[j] != '<' && str[j] != '\0' && str[j] > 32)
			j++;
	}
	ft_lstadd_back_redirect(&tmp->head_redirect, \
	ft_lstnew_redirect(flag, ft_cutstr(str, start, j)));
	*i = j;
}
