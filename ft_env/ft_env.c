#include "minishell.h"



int	both_are_sys(t_shell *shell, int i)
{
	t_list	*tmp;
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



void	print_2d_massive(char **mass)
{
	int i = -1;
	while (mass[++i])
		printf("%s\n", mass[i]);
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

void	renew_env_export_massive(t_shell *shell)
{
	list_to_2D_massive_env(shell);
	list_to_2D_massive_export(shell);
}

void	unset_env(t_shell *shell, char *key)
{
	t_list	*tmp;
	t_list	*prev;

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

void	export_env(t_shell *shell, char *string) // Скетч, нужно доработать
{
	ft_lstadd_back(&shell->head_env, ft_lstnew_initial(string));
	renew_env_export_massive(shell);
}

int	main(int argc, char **argv, char **env) // Нужно добавить free
{
	t_shell shell;
	
	shell.head_env = NULL;
	shell.original_env = env;
	shell.current_env = NULL;
	shell.current_export = NULL;
	env_to_list(&shell);
	print_list(shell.head_env);
	unset_env(&shell, "MANPATH");
	export_env(&shell, "check");
	export_env(&shell, "ABC=chekislav");
	printf("\n\n\n\n");
	print_list(shell.head_env);
	printf("\n\n\n\n");
	print_2d_massive(shell.current_env);
	printf("\n\n\n\n");
	print_2d_massive(shell.current_export);
	// while (1);
	t_list *tmp = shell.head_env;
	
	// while (tmp)
	// {
	// 	printf("%d\n", tmp->sys);
	// 	tmp = tmp->next;
	// }
	return (0);
}
