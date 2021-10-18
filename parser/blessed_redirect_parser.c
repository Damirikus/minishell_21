#include "../minishell.h"

void	pipe_flag_putter(t_list **head_command)
{
	t_list	*tmp;

	tmp = ft_lstlast(*head_command);
	tmp->flag_for_pipe = 0;
}

void	redirect_flag_putter(t_list *list)
{
	t_redirect	*tmp;
	t_redirect	*prev_in;
	t_redirect	*prev_out;

	prev_in = NULL;
	prev_out = NULL;
	tmp = list->head_redirect;
	while (tmp)
	{
		if (tmp->flag_for_stdin)
		{
			if (prev_in)
				prev_in->flag = 0;
			prev_in = tmp;
			prev_in->flag = 1;
		}
		else if (tmp->flag_for_stdout)
		{
			if (prev_out)
				prev_out->flag = 0;
			prev_out = tmp;
			if (tmp->flag_for_strange == 0)
				prev_out->flag = 1;
		}
		tmp = tmp->next;
	}
}

void	redirect_cutter(char **pipe_mass, int number, int i)
{
	char	*result;
	int		start;
	int		j;

	start = i;
	j = 0;
	while (pipe_mass[number][i] < 33 || pipe_mass[number][i] == '>' || pipe_mass[number][i] == '<')
		i++;
	while (pipe_mass[number][i] != '\0' && pipe_mass[number][i] > 32 && pipe_mass[number][i] != '<' && pipe_mass[number][i] != '>')
	{
		if (pipe_mass[number][i] == '\'' || pipe_mass[number][i] == '\"')
			ft_skip_quotes(pipe_mass[number], &i);
		if (pipe_mass[number][i] != '\0' && pipe_mass[number][i] != '\'' && pipe_mass[number][i] != '\"' \
		&& pipe_mass[number][i] != '>' && pipe_mass[number][i] != '<' && pipe_mass[number][i] > 32)
			i++;
	}
	result = malloc(sizeof(char) * (ft_strlen_g(pipe_mass[number]) - (i - start) + 1));
	while (j < start)
	{
		result[j] = pipe_mass[number][j];
		j++;
	}
	while (pipe_mass[number][i])
	{
		result[j] = pipe_mass[number][i];
		i++;
		j++;
	}
	result[j] = 0;
	free(pipe_mass[number]);
	pipe_mass[number] = result;
}


void	redirect_cut_from_str(char **pipe_mass)
{
	int	number;
	int	i;

	i = 0;
	number = 0;
	while (pipe_mass[number])
	{
		i = 0;
		while (pipe_mass[number][i])
		{
			if (pipe_mass[number][i] == '\"' || pipe_mass[number][i] == '\'')
				ft_skip_quotes(pipe_mass[number], &i);
			if (pipe_mass[number][i] == '>' || pipe_mass[number][i] == '<')
			{
				redirect_cutter(pipe_mass, number, i);
				i = -1;
			}
			if (i == -1 || (pipe_mass[number][i] != '\"' && pipe_mass[number][i] != '\'' && pipe_mass[number][i] != '\0'))
				i++;
		}
		number++;
	}
}

void	add_redirect(char *str, t_list *tmp, int *i) // Листы не зафришены
{
	int	j;
	int	flag;
	int	start;
	
	j = *i + 1;
	if (str[j - 1] == '<' && str[j] == '>')
	{
		flag = 5;
		j++;
	}
	else if (str[j] == '>')
	{
		flag = 2;
		j++;
	}
	else if (str[j] == '<')
	{
		flag = 4;
		j++;
	}
	else if (str[j] != '>' && str[j] != '<' && str[j - 1] == '>')
		flag = 1;
	else if (str[j] != '>' && str[j] != '<' && str[j - 1] == '<')
		flag = 3;
	while (str[j] != '\0' && str[j] < 33)
		j++;
	start = j;
	while (str[j] != '\0' && str[j] != '>' && str[j] != '<' && str[j] > 32)
	{
		if (str[j] == '\'' || str[j] == '\"')
			ft_skip_quotes(str, &j);
		if (str[j] != '\'' && str[j] != '\"' && str[j] != '>' && str[j] != '<' && str[j] != '\0' && str[j] > 32)
			j++;
	}
	ft_lstadd_back_redirect(&tmp->head_redirect, ft_lstnew_redirect(flag, ft_cutstr(str, start, j)));
	*i = j;
}

void	create_new_command_list(char **pipe_mass, t_list **head_command, int number) //  Создаем основные листы, и листы редиректов в них
{
	t_list	*tmp;
	int		i;
	
	i = 0;
	ft_lstadd_back(head_command, ft_lstnew(NULL, NULL));
	tmp = ft_lstlast(*head_command);
	while (pipe_mass[number][i])
	{
		if (pipe_mass[number][i] == '\"' || pipe_mass[number][i] == '\'')
			ft_skip_quotes(pipe_mass[number], &i);
		if (pipe_mass[number][i] == '>' || pipe_mass[number][i] == '<')
			add_redirect(pipe_mass[number], tmp, &i);
		if (pipe_mass[number][i] != '\"' && pipe_mass[number][i] != '\'' && pipe_mass[number][i] != '\0' && pipe_mass[number][i] != '<' && pipe_mass[number][i] != '>')
			i++;
	}
}

void	redirect_parser(char **pipe_mass, t_list **head_command)
{
	int	i;
	t_list *tmp;

	i = 0;
	while (pipe_mass[i])
	{
		create_new_command_list(pipe_mass, head_command, i);
		i++;
	}
	redirect_cut_from_str(pipe_mass);
	tmp = *head_command;
	while (tmp)
	{
		redirect_flag_putter(tmp);
		tmp = tmp->next;
	}
	pipe_flag_putter(head_command);
}
