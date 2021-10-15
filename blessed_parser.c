/*
Такс такс такс что тут у нас а парсер ахах наканецта

0. Если мы дошли сюда, значит препарсер завершился без ошибок, то есть нет незакрытых пайпов, кавычек, редиректов.
1. Создаем двумерный чар-массив из оригинальной строки. То есть делим строку на подстроки, разделитель pipe.
2. Меняем(раскрываем) знак доллара.
3. Парсим редиректы, а затем вырезаем их.
4. Конечный парсинг в листы
5. Раскрываем кавычки

*/

#include "minishell.h"

void	ft_print_list(t_list *head_command) 
{
	t_list		*tmp;
	t_redirect	*redirect;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = head_command;
	while (tmp)
	{
		printf("lst_number: %d\n\n", i);
		if (tmp->head_redirect)
		{
			redirect = tmp->head_redirect;
			printf("Redirects:\n\n");
			j = 0;
			while (redirect)
			{
				printf("%d: stdin: %d stdout: %d flag: %d name: |%s|\n\n", j, redirect->flag_for_stdin, redirect->flag_for_stdout, redirect->flag, redirect->filename);
				redirect = redirect->next;
				j++;
			}
		}
		printf("flag_for_pipe: %d\n******************\n", tmp->flag_for_pipe);
		tmp = tmp->next;
		i++;
	}
}

////////			bash"erino"asdbashjkee		bash

void	list_free_redirect(t_redirect **redirect)
{
	t_redirect	*last;
	t_redirect	*pre;
	int			i;
	int			lst_size;

	i = 0;
	lst_size = ft_lstsize_redirect(*redirect);
	while (i < lst_size)
	{
		last = ft_lstlast_redirect(*redirect);
		pre = ft_lstprelast_redirect(*redirect);
		ft_lstclear_redirect(&last, &free);
		pre->next = NULL;
		i++;
	}
}

void	list_free_command(t_list **head)
{
	t_list	*last;
	t_list	*pre;
	int			i;
	int			lst_size;

	i = 0;
	lst_size = ft_lstsize(*head);
	while (i < lst_size)
	{
		last = ft_lstlast(*head);
		pre = ft_lstprelast(*head);
		ft_lstclear(&last, &free);
		pre->next = NULL;
		i++;
	}
	*head = NULL;
}

void	list_free_redirect_cmd(t_list *tmp)
{
	int	i;

	i = 0;
	while (tmp->cmd[i])
	{
		free(tmp->cmd[i]);
		i++;
	}
	free(tmp->cmd);
	list_free_redirect(&tmp->head_redirect);
}

void	list_free(t_list **head)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		list_free_redirect_cmd(tmp);
		tmp = tmp->next;
	}
	list_free_command(head);
}

t_list	*parser(char *str, char **env)
{
	char	**pipe_mass;
	t_list	*head_command;

	head_command = NULL;
	pipe_mass = ft_split_by_pipe(str);
	int i = -1;

//	while (pipe_mass[++i])
//		printf("%d: |%s|\n", i, pipe_mass[i]);
//////////////////////////////////////////////
	dollar_pull(pipe_mass, env);
	redirect_parser(pipe_mass, &head_command);
	cmd_maker(pipe_mass, &head_command);
	quotes_killer(&head_command);
//////////////////////////////////////////////
//	ft_print_list(head_command);
	i = 0;
	i = -1;
//	while (pipe_mass[++i])
//		printf("%d: |%s|\n", i, pipe_mass[i]);
	i = -1;
//	printf("\nComands: \n");
	t_list *tmp;
	tmp = head_command;
	int j = 0;
//	while (tmp)
//	{
//		j = 0;
//		while (tmp->cmd[j])
//		{
//			printf("%s ", tmp->cmd[j]);
//			j++;
//		}
//		printf("\n");
//		tmp = tmp->next;
//	}
	
//	list_free(&head_command);
	// list_free_redirect(&head_command->head_redirect);
	// ft_lstclear_redirect(&head_command->next->head_redirect, &free);
	while (pipe_mass[++i])
		free(pipe_mass[i]);
	free(pipe_mass);
	// while (1);
	return (head_command);
	
}
