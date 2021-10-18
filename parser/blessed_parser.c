/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blessed_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rphoebe <champenao@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:36:51 by rphoebe           #+#    #+#             */
/*   Updated: 2021/10/18 21:46:20 by rphoebe          ###   ########.fr       */
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

t_list	*parser(char *str, t_data *data)
{
	char	**pipe_mass;
	t_list	*head_command;
	int		i;

	head_command = NULL;
	pipe_mass = ft_split_by_pipe(str);
	int j = -1;
	redirect_parser(pipe_mass, &head_command);
	dollar_pull(pipe_mass, data);
	dollar_pull_for_redirect(head_command, data);
	cmd_maker(pipe_mass, &head_command);
	quotes_killer(&head_command);
	redirect_check(head_command);
	t_redirect *tmp = head_command->head_redirect;
	while (tmp)
	{
		printf("filename: %s in: %d out: %d flag: %d\n", tmp->filename, tmp->flag_for_stdin, tmp->flag_for_stdout, tmp->flag);
		tmp = tmp->next;
	}
	exit (0);
	i = -1;
	while (pipe_mass[++i])
		free(pipe_mass[i]);
	free(pipe_mass);
	return (head_command);
}
