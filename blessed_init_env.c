#include "minishell.h"

void	print_list_env1(t_env *head)
{
	t_env *tmp;
	
	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	print_2d_massive(char **mass, t_list *list)
{
	int i = -1;

	while (mass[++i])
	{
		ft_putstr_fd(mass[i], 1);
		write(1, "\n", 1);
	}
	code_exit = 0;
}

void	env_to_list(t_data *shell) //  Оригинальные переменные окружения в листы и обратно
{
	int	i;

	i = -1;
	while (shell->original_env[++i])
		ft_lstadd_back_env(&shell->head_env, ft_lstnew_initial_env(shell->original_env[i]));
	list_to_2D_massive_env(shell);
	list_to_2D_massive_export(shell);
}

int	both_are_sys(t_data *shell, int i)
{
	t_env	*tmp;
	int		first_match;
	int		second_match;

	first_match = 0;
	second_match = 0;
	tmp = shell->head_env;
	while (tmp)
	{
		if (ft_strcmp(shell->current_export[i] + 11, tmp->content) == 0 || ft_strcmp(shell->current_export[i + 1] + 11, tmp->content) == 0)
		{
			if (tmp->sys == 1 && ft_strcmp(shell->current_export[i] + 11, tmp->content) == 0)
				first_match = 1;
			if (tmp->sys == 1 && ft_strcmp(shell->current_export[i + 1] + 11, tmp->content) == 0)
				second_match = 1;
		}
		tmp = tmp->next;
	}
	if (first_match == 1 && second_match == 1)
		return (1);
	return (0);
}


void	list_to_2D_massive_env(t_data *shell) // Листы в двойной чар-массив для execve
{
	int		i;
	t_env	*tmp;

	if (shell->current_env)
		free(shell->current_env);
	// 	ft_free_for_env(shell);
	shell->current_env = malloc(sizeof(char *) * (ft_lstsize_env(shell->head_env) + 1));
	i = -1;
	tmp = shell->head_env;
	while (++i < ft_lstsize_env(shell->head_env))
	{
		shell->current_env[i] = tmp->content;
		tmp = tmp->next;
	}
	shell->current_env[i] = NULL;
}


void	list_to_2D_massive_export(t_data *shell)
{
	int		i;
	int		j;
	t_env	*tmp;
	char	*str;

	if (shell->current_export)
		ft_free_for_export(shell);
	shell->current_export = malloc(sizeof(char *) * (ft_lstsize_env(shell->head_env) + 1));
	i = -1;
	j = 0;
	tmp = shell->head_env;
	while (++i < ft_lstsize_env(shell->head_env))
	{
		if (!(tmp->content[0] == '_' && tmp->content[1] == '='))
		{
			str = add_quotes(tmp->content);
			shell->current_export[j] = ft_strjoin_export("declare -x ", str);
			// shell->current_export[j] = ft_strjoin_export("declare -x ", tmp->content);
			free(str);
			j++;
		}
		tmp = tmp->next;
	}
	shell->current_export[j] = NULL;
	list_to_2D_massive_export_sort_sys(shell);
}

void	ft_free_for_export(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->current_export[i])
	{
		free(shell->current_export[i]);
		i++;
	}
	free(shell->current_export);
}

void	ft_free_for_env(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->current_env[i])
	{
		free(shell->current_env[i]);
		i++;
	}
	free(shell->current_env);
}

void	list_to_2D_massive_export_sort_sys(t_data *shell)
{
	int	i;
	char *tmp;

	// i = -1;
	i = 0;
	// while (i < ft_lstsize_env(shell->head_env) - 2)
	while (shell->current_export[i])
	{
		if (shell->current_export[i + 1] != NULL) {
		if (ft_strcmp(shell->current_export[i], shell->current_export[i + 1]) == 1)
		{
			tmp = shell->current_export[i];
			shell->current_export[i] = shell->current_export[i + 1];
			shell->current_export[i + 1] = tmp;
			i = -1;
		}
		}
		i++;
	}
}
