#include "minishell.h"

int ft_chek_all_files(t_list *list)
{
	t_list *current;
	t_redirect *redent;
	int len;
	len = 0;
	current = list;
	while (current)
	{
		len++;
//		if (current->flag_for_pipe == 1)
//		{
//			ft_open_pipe(current);
//		}
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


int ft_open_pipe(t_list *list)
{
	int fd[2];

	pipe(fd);
	list->fd1 =fd[1];
	list->next->fd0 = fd[0];
	return (0);
}


int ft_creat_chek_files(t_list *list, t_redirect *redirect)
{

	if (redirect->flag_for_stdout == 1 && list->flag_for_job == 0)
	{
		list->fd1 = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (list->fd1 == -1)
		{
			printf("Error: file not open\n");
			code_exit = 2;
			return (1);
		}
		if (redirect->flag != 1)
		{
			close(list->fd1);
			list->fd1 = -1;
		}
	}
	else if (redirect->flag_for_stdout == 2 && list->flag_for_job == 0)
	{
		list->fd1 = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (list->fd1 == -1)
		{
			printf("Error: file not open\n");
			code_exit = 2;
			return (1);
		}
		if (redirect->flag != 1)
		{
			close(list->fd1);
			list->fd1 = -1;
		}
	}
	else if (redirect->flag_for_stdin == 1 && list->flag_for_job == 0)
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
	}
	else if (redirect->flag_for_stdin == 2)
	{
		ft_key_handler(list, redirect);
	}
	return (0);
}

void ft_emp(int sig)
{
	(void)sig;
	rl_done = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int ft_key_handler(t_list *list, t_redirect *redirect)
{
	int td[2];
	char *str;
	int pid;

//	void *sg;

//	signal(SIGQUIT, SIG_IGN);
//	(sg = rl_getc_function);
//	rl_getc_function = getc;
	if (redirect->flag == 0)
	{
		while (1)
		{
			str = readline("> ");
			if (!str)
				break;
			if (!strcmp(str, redirect->filename))
			{
				signal(SIGINT, ft_ctrl);
//				signal(SIGQUIT, SIG_IGN);
				return (0);
			}
		}
	}
	else if (redirect->flag == 1)
	{
		pipe(td);
//		if (list->fd0 != -1)
//			close(list->fd0);
		list->fd0 = td[0];
		while (1)
		{
			str = readline("> ");
			if (!str)
				break;
			if (!strcmp(str, redirect->filename))
			{
				free(str);
				close(td[1]);
				signal(SIGINT, ft_ctrl);
//				signal(SIGQUIT, SIG_IGN);
				return (0);
			}
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				close(td[0]);
				dup2(td[1], 1);
				printf("%s\n", str);
				close(td[1]);
				free(str);
				exit(0);
			}
			if (pid != 0)
			{
				wait(NULL);
				free(str);
			}
		}

	}
	signal(SIGINT, ft_ctrl);
//	signal(SIGQUIT, SIG_IGN);
	return (0);
}
