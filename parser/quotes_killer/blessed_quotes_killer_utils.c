/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_quotes_killer_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 20:57:53 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 21:09:39 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quotes_killer_result_len_skip(char *name, int *i, int *result)
{
	if (name[*i] == '\'')
	{
		*i = *i + 1;
		while (name[*i] != '\'')
		{
			*i = *i + 1;
			*result = *result + 1;
		}
		return ;
	}
	if (name[*i] == '\"')
	{
		*i = *i + 1;
		while (name[*i] != '\"')
		{
			*i = *i + 1;
			*result = *result + 1;
		}
		return ;
	}
}

int	quotes_killer_result_len(char *name)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '\'' || name[i] == '\"')
			quotes_killer_result_len_skip(name, &i, &result);
		if (name[i] != '\'' && name[i] != '\"')
			result++;
		if (name[i] != 0)
			i++;
	}
	return (result + 1);
}
