#include "minishell.h"

void	shlvl_plus(t_data *data)
{
	t_env	*tmp;
	int		value;
	char	*value_char;

	tmp = data->head_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "SHLVL", ft_strlen_key(tmp->content)) && ft_strlen_key("SHLVL") == ft_strlen_key(tmp->content))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		value = ft_atoi(tmp->content + ft_strlen_key(tmp->content) + 1);
		value_char = ft_itoa(value + 1);
		free(tmp->content);
		tmp->content = ft_strjoin_export("SHLVL=", value_char);
		free(value_char);
		renew_env_export_massive(data);
	}
}
