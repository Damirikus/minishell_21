#include "minishell.h"


void	check_quotes_skip(char *str, int *i, int code)
{
	if (code == 2)
	{
		while (str[*i] != '\"' && str[*i] != '\0')
			*i = *i + 1;
		if (str[*i] == '\0')
			ft_error(1);
		else
			*i = *i + 1;
	}
	else if (code == 1)
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i + 1;
		if (str[*i] == '\0')
			ft_error(1);
		else
			*i = *i + 1;
	}
}

void	check_quotes(char *str, int *i)
{
	if (str[*i] == '\"')
	{
		*i = *i + 1;
		check_quotes_skip(str, i, 2);
			// return (1);
	}
	if (str[*i] == '\'')
	{
		*i = *i + 1;
		check_quotes_skip(str, i, 1);
			// return (1);
	} // 'l''s' "-l'a" | wc '-"l'
}

void	check_pipe(char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '|')
		ft_error(2);
	j = *i + 1;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '|')
		ft_error(2);
	if (str[j] == '\0')
		ft_error(3);
}

void	check_redir(char *str, int *i) //wc -l > ""
{
	int	j;
	
	if (str[*i] == '>' && str[*i + 1] == '<')
		ft_error(4);
	if ((str[*i] == '<' && str[*i + 1] == '>' ) || (str[*i] == '>' && str[*i + 1] == '|'))
		ft_error(5);
	if ((str[*i] == '<' && str[*i + 1] == '<') || (str[*i] == '>' && str[*i + 1] == '>'))
		j = *i + 2;
	else
		j = *i + 1;
	while (str[j] < 33 && str[j] != '\0')
		j++;
	if (str[j] == '\0')
		ft_error(5);
	if (str[j] == '|')
		ft_error(2);
	if (str[j] == '<')
		ft_error(4);
	if (str[j] == '>')
		ft_error(6);
}

void	check_pipe_redir(char *str, int *i)
{
	if (str[*i] == '|')
		check_pipe(str, i);
	if (str[*i] == '<' || str[*i] == '>')
		check_redir(str, i);
}
