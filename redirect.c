#include "minishell.h"

int	ft_chek_all_files(t_list *list, t_data *data)
{
	t_list		*current;
	t_redirect	*redent;
	int			len;

	len = 0;
	current = list;
	while (current)
	{
		len++;
		if (current->head_redirect)
		{
			redent = current->head_redirect;
			while (redent)
			{
				ft_creat_chek_files(current, redent, data);
				redent = redent->next;
			}
		}
		current = current->next;
	}
	ft_key_handler_creat(list, data);
	return (len);
}

int	ft_key_handler_creat(t_list *list, t_data *data)
{
	t_list		*current;
	t_redirect	*redent;

	current = list;
	while (current)
	{
		if (current->head_redirect)
		{
			redent = current->head_redirect;
			while (redent)
			{
				if (f == 1)
					return (0);
				if (redent->flag_for_stdin == 2)
					ft_key_handler(current, redent, data);
				redent = redent->next;
			}
		}
		current = current->next;
	}
	return (0);
}

int	ft_creat_chek_files(t_list *list, t_redirect *redirect, t_data *data)
{
	if (redirect->flag_for_stdout == 1 && list->flag_for_job == 0)
	{
		if (ft_stdout(list, redirect))
			return (1);
	}
	else if (redirect->flag_for_stdout == 2 && list->flag_for_job == 0)
	{
		if (ft_stdoutout(list, redirect))
			return (1);
	}
	else if (redirect->flag_for_stdin == 1 && list->flag_for_job == 0)
	{
		if (!ft_stdin(list, redirect))
			return (1);
	}
	return (0);
}

int	ft_stdout(t_list *list, t_redirect *redirect)
{
	list->fd1 = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (list->fd1 == -1)
	{
		list->flag_for_job = 1;
		list->filename_for_job = redirect->filename;
		return (1);
	}
	if (redirect->flag != 1)
	{
		close(list->fd1);
		list->fd1 = -1;
	}
	return (0);
}

int	ft_stdoutout(t_list *list, t_redirect *redirect)
{
	list->fd1 = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (list->fd1 == -1)
	{
		list->flag_for_job = 1;
		list->filename_for_job = redirect->filename;
		return (1);
	}
	if (redirect->flag != 1)
	{
		close(list->fd1);
		list->fd1 = -1;
	}
	return (0);
}

int	ft_stdin(t_list *list, t_redirect *redirect)
{
	list->fd0 = open(redirect->filename, O_RDONLY, 0644);
	if (list->fd0 == -1)
	{
		list->flag_for_job = 1;
		list->filename_for_job = redirect->filename;
		return (0);
	}
	if (redirect->flag != 1)
	{
		close(list->fd0);
		list->fd0 = -1;
	}
	return (1);
}

void	ft_emp(int sig)
{
	(void)sig;
	f = 1;
}

int	ft_key_handler_2(void *sg, t_redirect *redirect)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (!strcmp(tmp, redirect->filename))
		{
//			rl_getc_function = sg;
//			signal(SIGINT, ft_ctrl);
//			signal(SIGQUIT, ft_hz);
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int ft_key_handler_3(t_list *list, t_redirect *redirect, t_data *data)
{
	char	*str;
	int		pid;
	printf("HERERERERERER\n");
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			close(data->td[1]);
			break ;
		}
		if (!strcmp(str, redirect->filename))
		{
			free(str);
			close(data->td[1]);
			rl_getc_function = data->sg;
			signal(SIGINT, ft_ctrl);
			signal(SIGQUIT, ft_hz);
			return (0);
		}
		pid = fork();
		if (pid == 0)
		{
			close(data->td[0]);
			dup2(data->td[1], 1);
			close(data->td[1]);
			printf("%s\n", str);
			free(str);
			exit(0);
		}
		if (pid != 0)
		{
			wait(NULL);
			free(str);
		}
	}
	return (0);
}

int	ft_key_handler(t_list *list, t_redirect *redirect, t_data *data)
{
	signal(SIGINT, ft_emp);
	signal(SIGQUIT, SIG_IGN);
	rl_getc_function = getc;
	printf("%d\n", redirect->flag);
	if (redirect->flag == 0)
		return (ft_key_handler_2(data->sg, redirect));
	else if (redirect->flag == 1)
	{
		pipe(data->td);
		list->fd0 = data->td[0];
		return (ft_key_handler_3(list, redirect, data));
	}
	return (0);
}

