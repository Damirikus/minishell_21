#include "minishell.h"

int	check_name_unset(char *str)
{
	int	i;

	i = 0;
	if (!isalpha(str[i]))
	{
		printf("bash: unset: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (isalnum(str[i]))
		i++;
	if (str[i] != '\0')
	{
		printf("bash: unset: `%s': not a valid identifier\n", str);
		return (1);
	}
	return (0);
}

int	ft_strlen_key(char *str)
{
	int	i;
	
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
	
}

void	renew_env_export_massive(t_data *shell)
{
	list_to_2D_massive_env(shell);
	list_to_2D_massive_export(shell);
}

void	unset_env(t_data *shell, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = shell->head_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, key, ft_strlen_key(tmp->content)) == 0)
		{
			if (ft_strcmp(tmp->content, shell->head_env->content) == 0) // Условие для самого первого элемента
			{
				shell->head_env = shell->head_env->next;
				free(tmp->content);
				free(tmp);
				break ;
			}
			prev->next = tmp->next;
			free(tmp->content);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	renew_env_export_massive(shell);
}

void	export_env(t_data *shell, char *string) // Скетч, нужно доработать
{
	ft_lstadd_back_env(&shell->head_env, ft_lstnew_initial_env(string));
	renew_env_export_massive(shell);
}
