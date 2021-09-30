#include "minishell.h"

int	cmd_allocator_helper(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] != '\0' && str[i] < 33)
		i++;
	while (str[i] != '\0')
	{
		while (str[i] > 32 && str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
				ft_skip_quotes(str, &i);
			if (str[i] > 32 && str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
				i++;
		}
		result++;
		while (str[i] < 33 && str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
			i++;
	}
	printf("result: %d\n", result);
	return (result + 1);
}

void	cmd_allocator(char **pipe_mass, t_list **head_command)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head_command;
	while (pipe_mass[i])
	{
		tmp->cmd = malloc(sizeof(char *) * cmd_allocator_helper(pipe_mass[i]));
		tmp = tmp->next;
		i++;
	}
}

void	cmd_pull_helper(char *str, t_list *tmp)
{
	int	i;
	int	start;
	int	number;

	i = 0;
	number = 0;
	while (str[i] != '\0' && str[i] < 33)
		i++;
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] > 32 && str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
				ft_skip_quotes(str, &i);
			if (str[i] > 32 && str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
				i++;
		}
		tmp->cmd[number] = ft_cutstr(str, start, i);
		number++;
		while (str[i] < 33 && str[i] != '\0')
			i++;
	}
	tmp->cmd[number] = NULL;
}

void	cmd_pull(char **pipe_mass, t_list **head_command)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head_command;
	while (pipe_mass[i])
	{
		cmd_pull_helper(pipe_mass[i], tmp);
		tmp = tmp->next;
		i++;
	}
}

void	cmd_maker(char **pipe_mass, t_list **head_command)
{
	cmd_allocator(pipe_mass, head_command);
	cmd_pull(pipe_mass, head_command);
}
