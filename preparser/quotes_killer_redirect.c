#include "preparser.h"

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

int	quotes_killer_result_len(char *name) // Считаем длину итоговой строки без кавычек
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
	// printf("Xname: %s len: %d\n", name, result + 1);
	return (result + 1);
}

void	quotes_killer_redirect_helper_copy(char *result, char *name, int *i, int *j) // копирует то что вы кавыках
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

void	quotes_killer_redirect_helper(t_redirect *tmp)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * quotes_killer_result_len(tmp->filename));
	while (tmp->filename[i])
	{
		if (tmp->filename[i] == '\'' || tmp->filename[i] == '\"')
			quotes_killer_redirect_helper_copy(result, tmp->filename, &i, &j);
		if (tmp->filename[i] != '\'' && tmp->filename[i] != '\"')
		{
			result[j] = tmp->filename[i];
			j++;
		}
		if (tmp->filename[i] != 0)
			i++;
	}
	result[j] = 0;
	free(tmp->filename);
	tmp->filename = result;
}

void	quotes_killer_redirect(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		quotes_killer_redirect_helper(tmp);
		tmp = tmp->next;
	}
}

void	quotes_killer(t_list **head_command)
{
	t_list	*tmp;

	tmp = *head_command;
	while (tmp)
	{
		quotes_killer_redirect(tmp->head_redirect);
		quotes_killer_command(tmp);
		tmp = tmp->next;
	}
}
