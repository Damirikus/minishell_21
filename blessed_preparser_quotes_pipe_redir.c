#include "minishell.h"


int	check_quotes_skip(char *str, int *i, int code)
{
	if (code == 2)
	{
		while (str[*i] != '\"' && str[*i] != '\0')
			*i = *i + 1;
		if (str[*i] == '\0')
			return(ft_error(1));
		else
			*i = *i + 1;
	}
	else if (code == 1)
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i + 1;
		if (str[*i] == '\0')
			return(ft_error(1));
		else
			*i = *i + 1;
	}
	return (0);
}

int	check_quotes(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		if (check_quotes_skip(str, i, 2))
			return (1);
	}
	if (str[*i] == '\'')
	{
		*i = *i + 1;
		if (check_quotes_skip(str, i, 1))
			return (1);
	}
	return (0);
}

int	check_pipe(char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '|')
		return (ft_error(2));
	j = *i + 1;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '|')
		return (ft_error(2));
	if (str[j] == '\0')
		return (ft_error(3));
	return (0);
}

int	check_redir(char *str, int *i)
{
	int	j;

	if (str[*i] == '>' && str[*i + 1] == '<')
		return (ft_error(4));
	if ((str[*i] == '>' && str[*i + 1] == '|'))
		return (ft_error(5));
	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && \
	 str[*i + 1] == '>') || (str[*i] == '<' && str[*i + 1] == '>'))
		j = *i + 2;
	else
		j = *i + 1;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '\0')
		return (ft_error(5));
	if (str[j] == '|')
		return (ft_error(2));
	if (str[j] == '<')
		return (ft_error(4));
	if (str[j] == '>')
		return (ft_error(6));
	return (0);
}

int	check_pipe_redir(char *str, int *i)
{
	if (str[*i] == '|')
		return (check_pipe(str, i));
	if (str[*i] == '<' || str[*i] == '>')
		return (check_redir(str, i));
	return (0);
}
