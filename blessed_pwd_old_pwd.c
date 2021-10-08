#include "minishell.h"

void	set_current_dir_name(t_data *data)
{
	data->current_pwd = malloc(404);
	getcwd(data->current_pwd, 404);
}

void	pwd_oldpwd_remaker(t_data *data)
{
	t_env	*tmp_pwd;

	tmp_pwd = data->head_env;
	while (tmp_pwd)
	{
		if (ft_strncmp(tmp_pwd->content, "PWD", 3) && tmp_pwd->content[3] == '=')
			data->current_pwd = ft_cutstr(tmp_pwd->content, 4, -1);
		tmp_pwd = tmp_pwd->next;
	}
}
