#include "preparser.h"

void	quotes_killer_command_helper_copy(char *result, char *name, int *i, int *j) // копирует то что вы кавыках
{
	if (name[*i] == '\'')
	{
		*i = *i + 1;
		while (name[*i] != '\'')
		{
			result[*j] = name[*i];
			*j = *j + 1;
			*i = *i + 1;
		}
		return ;
	}
	if (name[*i] == '\"')
	{
		*i = *i + 1;
		while (name[*i] != '\"')
		{
			result[*j] = name[*i];
			*j = *j + 1;
			*i = *i + 1;
		}
		return ;
	}
}

void	quotes_killer_command_helper(t_list *tmp, int number)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * quotes_killer_result_len(tmp->cmd[number]));
	while (tmp->cmd[number][i])
	{
		if (tmp->cmd[number][i] == '\'' || tmp->cmd[number][i] == '\"')
			quotes_killer_command_helper_copy(result, tmp->cmd[number], &i, &j);
		if (tmp->cmd[number][i] != '\'' && tmp->cmd[number][i] != '\"')
		{
			result[j] = tmp->cmd[number][i];
			j++;
		}
		// if (tmp->cmd[number][i] != 0 && tmp->cmd[number][i] != '\'' && tmp->cmd[number][i] != '\"')
		if (tmp->cmd[number][i] != 0)
			i++;
	}
	result[j] = 0;
	free(tmp->cmd[number]);
	tmp->cmd[number] = result;
}

void	quotes_killer_command(t_list *head_command)
{
	t_list	*tmp;
	int		number;

	tmp = head_command;
	number = 0;
	while (tmp->cmd[number])
	{
		quotes_killer_command_helper(tmp, number);
		number++;
	}
}
