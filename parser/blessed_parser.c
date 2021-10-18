/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:36:51 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/16 23:39:25 by rphoebe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_check(t_list *head_command)
{
	t_list		*tmp;
	t_redirect	*tmp_red;

	tmp = head_command;
	while (tmp)
	{
		tmp_red = tmp->head_redirect;
		while (tmp_red)
		{
			if (tmp_red->flag_for_stdin == 2 && tmp_red->filename[0] == '\0')
				tmp_red->flag = 0;
			tmp_red = tmp_red->next;
		}
		tmp = tmp->next;
	}
}

t_list	*parser(char *str, char **env)
{
	char	**pipe_mass;
	t_list	*head_command;
	int		i;

	head_command = NULL;
	pipe_mass = ft_split_by_pipe(str);
	redirect_parser(pipe_mass, &head_command);
	dollar_pull(pipe_mass, env);
	dollar_pull_for_redirect(head_command, env);
	cmd_maker(pipe_mass, &head_command);
	quotes_killer(&head_command);
	redirect_check(head_command);
	i = -1;
	while (pipe_mass[++i])
		free(pipe_mass[i]);
	free(pipe_mass);
	return (head_command);
}
