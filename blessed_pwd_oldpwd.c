#include "minishell.h"

void	pwd_remaker(t_data *data)
{
	t_env	*tmp_pwd;

	tmp_pwd = data->head_env;
	while (tmp_pwd)
	{
		if (ft_strncmp(tmp_pwd->content, "PWD", ft_strlen_key(tmp_pwd->content)) == 0 && \
		 ft_strlen_key(tmp_pwd->content) == strlen("PWD"))
		{
			data->current_pwd = ft_cutstr(tmp_pwd->content, 0, -1);
			free(tmp_pwd->content);
			tmp_pwd->content = data->current_pwd;
			break ;
		}
		tmp_pwd = tmp_pwd->next;
	}
}

void	oldpwd_remaker(t_data *data)
{
	t_env	*tmp_pwd;

	tmp_pwd = data->head_env;
	while (tmp_pwd)
	{
		if (ft_strncmp(tmp_pwd->content, "OLDPWD", ft_strlen_key(tmp_pwd->content)) == 0 \
		&& ft_strlen_key(tmp_pwd->content) == strlen("OLDPWD"))
		{
			data->current_oldpwd = ft_cutstr(tmp_pwd->content, 0, -1);
			free(tmp_pwd->content);
			tmp_pwd->content = data->current_oldpwd;
			break ;
		}
		tmp_pwd = tmp_pwd->next;
	}
}

void	pwd_oldpwd_remaker(t_data *data)
{
	pwd_remaker(data);
	oldpwd_remaker(data);
	renew_env_export_massive(data);
}

void	renew_oldpwd(t_data *data)
{
	free(data->current_oldpwd);
	char *str = ft_strjoin_export("OLD", data->current_pwd);
	data->current_oldpwd = str;
	printf("HERE: %s\n", str);
}

void	renew_pwd(t_data *data)
{
	char	*newpwd;

	newpwd = malloc(405);
	getcwd(newpwd, 405);
	free(data->current_pwd);
	data->current_pwd = ft_strjoin_export("PWD=", newpwd);
	free(newpwd);
}

void	renew_pwd_oldpwd(t_data *data)
{
	renew_oldpwd(data);
	// renew_pwd(data);
	// renew_env_export_massive(data);
}
