#include "minishell.h"


/*  
> прямой редирект
>> двойной прямой редирект
< обратный редирект
<< двойной обратный редирект



сюда приходит лист с заполненным листом редиректов
сначала происходит заполнение массива флагов для определения какой из типов редиректов,
обрабатываем 5 разных типов:
1) только > >> > > >> > (так как они работают одинаково, неважно кто последний)
2) < << < << < (здесь последним должен быть строго <, а двойные обратные редиректы будут работать как ключ)
3) < << < <<  (здсь послденим должен быть <<, а ординарный обратный редирект лишь проверяет наличие файлов, двойные обратные
до последнего двойного обратного редиректа работают как ключи)
4) < < << < > > < (здесь учитывается последний прямой и обратный редирект,  происходит запись из обратного редиректа в прямой,
при этом двойные обратные редиректы работают как ключи и не могут быть последними, то есть после них должен быть ординарный
 обратный редирект)
 5) < << > >> << (здесь происходит запись из двойного обратного редиректа в прямой редирект, все остальный прямые создают файлы
 все остальные обратные проверяют файлы и все остальные двойные обратные работают как ключи)
*/

int ft_redirections(t_list *list, char **path)
{
	t_redirect *current;
	int var[3];
	char *str;
	ft_bzero1(var, 3);
	current = list->head_redirect;
	
	while (current)
	{
		if (current->flag_for_stdout > 0 && current->flag == 1)
			var[0] = 1;
		if (current->flag_for_stdin == 1 && current->flag == 1)
			var[1] = 1;
		if (current->flag_for_stdin == 2 && current->flag == 1)
			var[2] = 1;
		current = current->next;
	}

	// распределяем все 5 вариантов(все работают по разному)
	// 1) в этом варианте обрабатываются только прямые редиректы
	// если команда идет до пайпа, сначала обрабатывается функция и записывается в файл,
	//после чего создается пустой дискриптор чтения, который заменяет материнский дискриптор
	// если посел пайпа, так же выполняется запись и возврат материнского дискрипттора
	if (var[0] == 1 && !var[1] && !var[2])
	{
		printf("11111\n");
		ft_first_variation(list, path);
		if (list->flag_for_pipe == 1)
			ft_pipe_redirect();
		if (list->flag_for_pipe == -1)
			dup2(list->pid_mother, 0);
		
		
	}
	//2) в данном варианте только обратные редиректы (последний - ординарный обратный)
	// если идет до пайпа, отправляется в функцию, где сначала создается пайп, в который записывается читаемое
	// и подменяется материнский дискриптор
	// если после пайпа, выполняется и возвращается материнский дискриптор
	if (!var[0] && var[1] == 1 && !var[2])
	{
		printf("222222\n");
		if (list->flag_for_pipe == 1)
			ft_pipe_redirect_out(path, list);
		if (list->flag_for_pipe == -1)
		{
			ft_second_variation(list, path);
			dup2(list->pid_mother, 0);
		}
		if (list->flag_for_pipe == 0)
			ft_second_variation(list, path);
			
	}
	//3) в данном варианте только обратные редиректы (последний - дыойной обратный)
	if (!var[0] && !var[1] && var[2] == 1)
	{
		printf("333333\n");
		if (list->flag_for_pipe == 1)
			ft_pipe_redirect_outout(path, list);
		// get_next_line(0, &str);
		// printf(" str = %s\n", str);
		if (list->flag_for_pipe == -1)
		{
			dup2(list->pid_mother, 0);
			ft_third_variation(list, path);
		}
		if (list->flag_for_pipe == 0)
			ft_third_variation(list, path);
	}
	//4) в данном прямой и обратный
	if (var[0] == 1 && var[1] == 1 && !var[2])
	{
		printf("444444\n");
		ft_fourth_variation(list, path);
		if (list->flag_for_pipe == 1)
			ft_pipe_redirect();
		if (list->flag_for_pipe == -1)
			dup2(list->pid_mother, 0);
			
	}
	// 5) прямой и двойной обратный
	if (var[0] == 1 && !var[1] && var[2] == 1)
	{
		printf("55555\n");
		ft_fifth_variation(list, path);
		if (list->flag_for_pipe == 1)
			ft_pipe_redirect();
		if (list->flag_for_pipe == -1)
			dup2(list->pid_mother, 0);
	}
	return (0);
}


//здесь все редиректы по очереди отправляем в аt_stdout которые создает все файлы, и если есть команда, исполняет его в последний файл
int ft_first_variation(t_list *list, char **path)
{
	t_redirect *current;
	current = list->head_redirect;
	
	while (current)
	{
		ft_stdout(path, list, current);
		current = current->next;
	}
	return (0);
}


int ft_second_variation(t_list *list, char **path)
{
	t_redirect *current;
	char **key;
	//сначала создаем массив со всеми ключами
	key = ft_creat_all_key(list);
	// далее обрабатываем все ключи
	if (key)
		ft_stdin_key(key);
	//ниже проверяем существуют ли все файлы, и если все существует, команда отправляется на исполнение в функцию ft_stdin
	current = list->head_redirect;
	while (current)
	{
		if (current->flag_for_stdin == 1)
		{
			if (ft_stdin(path, list, current) == 1)
				return (1);
		}
		current = current->next;
	}
	return (0);
}


int ft_third_variation(t_list *list, char **path)
{
	
	char **key;
	int fd[2];
	int pid;
	// char *str;
	t_redirect *current;
	//создаем все ключи в массиве
	key = ft_creat_all_key(list);
	pipe(fd);
	
	pid = fork();
	if (pid == 0)
	{
		//в дочке происходит исполнение всех ключей, а так же запись в пайп данных перед последним ключем
		dup2(fd[1], 1);
		close(fd[0]);
		ft_write_third_stdin(key);
		// get_next_line(0, &str);
		// printf(" str = %s\n", str);
		close(fd[1]);
		// exit(0);
	}
	if (pid != 0)
	{
		//мать при этом ожидает выполнения всех ключей и далее проверяет существуют ли все файлы
		wait(NULL);
		current = list->head_redirect;
		while (current)
		{
			if (current->flag_for_stdin == 1)
			{
				if (ft_stdin(path, list, current) == 1)
					return (1);
			}
			current = current->next;
		}
		//после проверки меняем дискриптор чтения на пайп, чтобы команда читала оттуда и отправляется на выполнение а ft_empty
		printf("SHEEET\n");
		dup2(fd[0], 0);
		close(fd[1]);
        ft_empty(path, list);
        dup2(list->pid_mother, 0);
		close(fd[0]);
	}
	
	return (0);
}

int ft_fourth_variation(t_list *list, char **path)
{
	t_redirect *current;
	t_redirect *pstdout;
	t_redirect *pstdin;
	int t;
	char **key;
	
	t = 0;
	//так же создаются все ключи и отправляются на обработку
	key = ft_creat_all_key(list);
	if (key)
		ft_stdin_key(key);
	current = list->head_redirect;
	// далее в функции ft_stdin gроверяется наличие файлов а в функции ft_stdout создаются все функции
	while (current)
	{
		if (current->flag_for_stdin == 1)
		{
			if (current->flag == 1)
			{
				current->flag = 0;
				t = 1;
			}
			if (ft_stdin(path, list, current) == 1)
				return (1);
			if (t == 1)
				current->flag = 1;
		}
		else if (current->flag_for_stdout > 0 && current->flag == 0)
		{
			ft_stdout(path, list, current);
		}
		else if (current->flag_for_stdout > 0 && current->flag == 1)
			pstdout = current;
		// когда цикл добирается до листов редиректов с флагом 1 , они запоминаются и отправляются на исполнение в ft_stdin_stdout
		if (current->flag_for_stdin == 1 && current->flag == 1)
			pstdin = current;
		current = current->next;
	}
	ft_stdin_stdout(list, path, pstdin, pstdout);
	return (0);
}

int ft_fifth_variation(t_list *list, char **path)
{
	char **key;
	int fd[2];
	int pid;
	t_redirect *pstdout;

	//создаем все ключи в массиве
	key = ft_creat_all_key(list);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		//в дочке происходит исполнение всех ключей, а так же запись в пайп данных перед последним ключем
		dup2(fd[1], 1);
		close(fd[0]);
		ft_write_third_stdin(key);
		close(fd[1]);
	}
	if (pid != 0)
	{
		wait(NULL);
		pstdout = ft_chek_files_fifth(list, path);
		if (pstdout == NULL)
			return (1);
		dup2(fd[0], 0);
		close(fd[1]);
		ft_stdout(path, list, pstdout);
	}
	return (0);
}








int ft_stdout(char **path, t_list *list, t_redirect *current)
{
	int fd;
	int pid;
	//создаются файлы и проверяются
	if (current->flag_for_stdout == 1)
	{	
		fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("Error: file not open\n");
			code_exit = 2;
			return(1);
		}
	}
	else if (current->flag_for_stdout == 2)
	{
		fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
		    printf("Error: file not open\n");
		    code_exit = 2;
		    return(1);
		}
	}
	if (current->flag == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			// в дочке меняем дескриптор ввода на файл
			dup2(fd, 1);
			ft_distributor(path, list);
			close(fd);
		}
		if (pid != 0)
		{
			//мать ждет 
			close(fd);
			wait(NULL);
			// dup2(list->pid_mother, 0);
		}
	}
	return (0);
}



int ft_stdin(char **path, t_list *list, t_redirect *current)
{
	int fd;
	int pid;

	//проверяет наличие файла
	fd = open(current->filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("miniHELL: %s: No such file or directory\n", current->filename);
		code_exit = 1;
		return (1);
	}
	if (current->flag == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			//в дочке меняет дескриптор чтения и отправляет на исполнение в дистрибутор
			dup2(fd, 0);
			ft_distributor(path, list);
			close(fd);
		}
		if (pid != 0)
		{
			close(fd);
			wait(NULL);
			// dup2(list->pid_mother, 0);
		}
	}
	return (0);
}



int ft_stdin_stdout(t_list *list, char **path, t_redirect *pstdin, t_redirect *pstdout)
{
	int fd_in;
	int pid;
	int fd_out;
	// проверки файлов
	fd_in = open(pstdin->filename, O_RDONLY, 0644);
	if (fd_in == -1)
	{
		printf("1Error: file not open\n");
		code_exit = 2;
		return(1);
	}
	if (pstdout->flag_for_stdout == 1)
	{	
		fd_out = open(pstdout->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			printf("2Error: file not open\n");
			code_exit = 2;
			return(1);
		}
	}
	else if (pstdout->flag_for_stdout == 2)
	{
		fd_out = open(pstdout->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
		{
		    printf("3Error: file not open\n");
		    code_exit = 2;
		    return(1);
		}
	}
		pid = fork();
		if (pid == 0)
		{
			//поток ввода и вывода меняются на файлы и отправляется на исполнение
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			ft_distributor(path, list);
			close(fd_in);
		}
		if (pid != 0)
		{
			close(fd_in);
			close(fd_out);
			wait(NULL);
			dup2(list->pid_mother, 0);
		}
		return (0);
}


//функция для выполнения ключей
int ft_stdin_key(char **key)
{
	char *str;
	int i;
	int count;
	count = 0;
	// printf ("sheeet\n");
	while (key[count])
		count++;
	// printf("COUNT %d\n", count);
	i = 0;
	while (i < count)
	{
		get_next_line(0, &str);
		if (!strcmp(str, key[i]))
			i++;
		free(str);
	}
	return (0);
}

//функция для выполнения ключей и записи данных перед последним ключем
int ft_write_third_stdin(char **key)
{
	char *str;
	int count;
	int i;
	
	count = 0;
	while (key[count])
		count++;
	i = 0;
	while(i != count)
	{
    	get_next_line(0, &str);
		if (i == count - 1)	
		{
			if (!strcmp(str, key[i]))
    			exit(0);
			printf("%s\n", str);
		}
		if (i < count - 1)
    		if (!strcmp(str, key[i]))
    			i++;
    	free(str);
	}
	return (0);
}




char **ft_creat_all_key(t_list *list)
{
	t_redirect *current;
	char **key;
	int i;
	
	current = list->head_redirect;
	i = 0;
	while (current)
	{
		if (current->flag_for_stdin == 2)
			i++;
		current = current->next;
	}
	key = malloc(sizeof(char *) * i + 1);
	key[i] = 0;
	current = list->head_redirect;
	i = 0;
	while (current)
	{
		if (current->flag_for_stdin == 2)
		{
			key[i] = malloc(ft_strlen(current->filename) + 1);
			ft_strlcpy(key[i], current->filename, ft_strlen(current->filename) + 1);
			i++;
		}
		current = current->next;
	}
	return (key);
}


t_redirect *ft_chek_files_fifth(t_list *list, char **path)
{
	t_redirect *current;
	t_redirect *pstdout;
	current = list->head_redirect;
	while (current)
	{
		if (current->flag_for_stdin == 1)
		{
			if (ft_stdin(path, list, current) == 1)
				return (NULL);
		}
		else if (current->flag_for_stdout > 0 && current->flag == 0)
		{
			ft_stdout(path, list, current);
		}
		else if (current->flag_for_stdout > 0 && current->flag == 1)
			pstdout = current;
		current = current->next;
	}
	
	return (pstdout);
}