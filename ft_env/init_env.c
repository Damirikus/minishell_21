/*  Изначальная инициализация листов enva, двойного массива enva, и двойного массива экспорта */



#include "minishell.h"

void	ft_free_for_export(t_shell *shell)
{
	int	i;
	
	i = -1;
	while (shell->current_export[++i])
		free(shell->current_export[i]);
	free(shell->current_export);
}

void	list_to_2D_massive_export_sort_sys(t_shell *shell)
{
	int	i;
	char *tmp;
	
	i = -1;
	while (++i < ft_lstsize(shell->head_env) - 2)
	{
		if (ft_strcmp(shell->current_export[i], shell->current_export[i + 1]) == 1)
		{
			tmp = shell->current_export[i];
			shell->current_export[i] = shell->current_export[i + 1];
			shell->current_export[i + 1] = tmp;
			i = -1;
		}
	}
}

void	list_to_2D_massive_export(t_shell *shell)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (shell->current_export)
		ft_free_for_export(shell);
	shell->current_export = malloc(sizeof(char *) * (ft_lstsize(shell->head_env) + 1));
	i = -1;
	j = 0;
	tmp = shell->head_env;
	while (++i < ft_lstsize(shell->head_env))
	{
		if (!(tmp->content[0] == '_' && tmp->content[1] == '='))
		{
			shell->current_export[j] = ft_strjoin_export("declare -x ", add_quotes(tmp->content));
			j++;
		}
		tmp = tmp->next;
	}
	shell->current_export[j] = NULL;
	list_to_2D_massive_export_sort_sys(shell);
}

void	list_to_2D_massive_env(t_shell *shell) // Листы в двойной чар-массив для execve
{
	int		i;
	t_env	*tmp;

	if (shell->current_env)
		free(shell->current_env);
	shell->current_env = malloc(sizeof(char *) * (ft_lstsize(shell->head_env) + 1));
	i = -1;
	tmp = shell->head_env;
	while (++i < ft_lstsize(shell->head_env))
	{
		shell->current_env[i] = tmp->content;
		tmp = tmp->next;
	}
	shell->current_env[i] = NULL;
}

void	env_to_list(t_shell *shell) //  Оригинальные переменные окружения в листы и обратно
{
	int	i;
	
	i = -1;
	while (shell->original_env[++i])
		ft_lstadd_back(&shell->head_env, ft_lstnew_initial(shell->original_env[i]));
	list_to_2D_massive_env(shell);
	list_to_2D_massive_export(shell);
}
