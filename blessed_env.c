#include "minishell.h"

int	check_name_unset(char *str)
{
	int	i;

	i = 0;
	if (!isalpha(str[i]) && str[i] != '_')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		code_exit = 1;
		return (1);
	}
	while (isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '\0')
	{
		printf("minishell: unset: `%s': not a valid identifier\n", str);
		code_exit = 1;
		return (1);
	}
	return (0);
}

int	check_name_export(char *str)
{
	int	i;

	i = 0;
	if (!isalpha(str[i]) && str[i] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		code_exit = 1;
		return (1);
	}
	while (isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] != '=' && str[i] != '\0')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		code_exit = 1;
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
		if (ft_strncmp(tmp->content, key, ft_strlen_key(tmp->content)) == 0 && ft_strlen_key(tmp->content) == ft_strlen_key(key))
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

int	export_env_variable_present(t_data *shell, char *str)
{
	t_env	*tmp;

	tmp = shell->head_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, ft_strlen_key(str)) == 0) // ????
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	export_env_variable_strong(char *string)
{
	int	i;

	i = 0;
	while (isalnum(string[i]) || string[i] == '_')
		i++;
	if (string[i] == '+')
		i++;
	if (string[i] == '=')
		return (1);
	return (0);
}

// char	*clean_string_export(char *string)
// {
// 	int		i;
// 	int		j;
// 	int		flag;
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	flag = 0;
// 	result = malloc(sizeof(char) * ft_strlen(string));
// 	while (string[i])
// 	{
// 		if (string[i] != '+' || flag)
// 		{
// 			result[j] = string[i];
// 			j++;
// 		}
// 		if (string[i] == '+')
// 			flag = 1;
// 		i++;
// 	}
// 	result[j] = 0;
// 	return (result);
// }

char	*clean_string_export(char *string)
{
	int		i;
	int		j;
	int		flag;
	char	*result;

	i = 0;
	j = 0;
	flag = 0;
	result = malloc(sizeof(char) * ft_strlen(string));
	while (string[i] != '\0' && string[i] != '+')
	{
		result[j] = string[i];
		i++;
		j++;
	}
	i++;
	while (string[i])
	{
		result[j] = string[i];
		i++;
		j++;
	}
	result[j] = 0;
	return (result);
}

void	export_env_append(t_data *shell, char *string)
{
	char	*clean_string;
	t_env	*tmp;

	clean_string = clean_string_export(string);
	if (!export_env_variable_present(shell, clean_string))
	{
		printf("yes4\n");
		ft_lstadd_back_env(&shell->head_env, ft_lstnew_initial_env(clean_string));
		free(clean_string);
		return ;
	}
	tmp = shell->head_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, clean_string, ft_strlen_key(clean_string)) == 0)
		{
			printf("yes5\n");
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp)
	{
		printf("yes6\n");
		if (!export_env_variable_strong(tmp->content))
			tmp->content = ft_strjoin_pars(tmp->content, "=");
	}
	tmp->content = ft_strjoin_pars(tmp->content, clean_string + ft_strlen_key(clean_string) + 1);
	free(clean_string);
	renew_env_export_massive(shell);
}

void	export_env(t_data *shell, char *string) // Скетч, нужно доработать
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen_key(string);
	printf("yes0\n");
	while (i < len)
	{
		if (string[i] == '+')
		{
			printf("yes1\n");
			export_env_append(shell, string);
			renew_env_export_massive(shell);
			return ;
		}
		i++;
	}
	if (export_env_variable_present(shell, string) && !export_env_variable_strong(string))
	{
		printf("yes2\n");
		return ;
	}
	if (export_env_variable_present(shell, string) && export_env_variable_strong(string))
	{
		printf("yes3\n");
		unset_env(shell, string);
	}
	ft_lstadd_back_env(&shell->head_env, ft_lstnew_initial_env(string));
	renew_env_export_massive(shell);
}
