/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_preparser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:18:36 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/16 23:22:58 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	preparser(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (check_quotes(str, &i))
				return (1);
		}
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			if (check_pipe_redir(str, &i))
				return (1);
		if (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			i++;
	}
	return (0);
}
