#include "minishell.h"

int	ft_chek_all_files(t_list *list)
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
				ft_creat_chek_files(current, redent);
				redent = redent->next;
			}
		}
		current = current->next;
	}
	return (len);
}

int	ft_creat_chek_files(t_list *list, t_redirect *redirect)
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
	else if (redirect->flag_for_stdin == 2)
		ft_key_handler(list, redirect);
	return (0);
}

int	ft_stdout(t_list *list, t_redirect *redirect)
{
	list->fd1 = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (list->fd1 == -1)
	{
		printf("minishell: : No such file or directory\n");
		code_exit = 2;
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
		printf("minishell: : No such file or directory\n");
		code_exit = 2;
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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	ft_key_handler_2(char **str, void *sg, t_redirect *redirect)
{
	char *tmp;

	tmp = *str;

	while (1)
	{
		*str = readline("> ");
		if (!tmp)
			break ;
		if (!strcmp(*str, redirect->filename))
		{
			rl_getc_function = sg;
			signal(SIGINT, ft_ctrl);
			signal(SIGQUIT, ft_hz);
			return (1);
		}
	}
	return (0);
}

int	ft_key_handler(t_list *list, t_redirect *redirect)
{
	int		td[2];
	char	*str;
	int		pid;
	void	*sg;

	signal(SIGINT, ft_emp);
	signal(SIGQUIT, SIG_IGN);
	(sg = rl_getc_function);
	rl_getc_function = getc;
	if (redirect->flag == 0)
		return (ft_key_handler_2(&str, sg, redirect));
	else if (redirect->flag == 1)
	{
		pipe(td);
		list->fd0 = td[0];
		while (1)
		{
			str = readline("> ");
			if (!str)
			{
				close(td[1]);
				break ;
			}
			if (!strcmp(str, redirect->filename))
			{
				free(str);
				close(td[1]);
				rl_getc_function = sg;
				signal(SIGINT, ft_ctrl);
				signal(SIGQUIT, ft_hz);
				return (0);
			}
			pid = fork();
			if (pid == 0)
			{
				close(td[0]);
				dup2(td[1], 1);
				close(td[1]);
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
		close(td[1]);
	}
	rl_getc_function = sg;
	signal(SIGINT, ft_ctrl);
	signal(SIGQUIT, ft_hz);
	return (0);
}

