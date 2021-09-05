#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
# include <time.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
# define RED "\x1B[31m"
# define WHITE "\x1B[37m"


char **ft_path(char *str);
void ft_echo(char *full_path, t_list *list);
int ft_pipe(char **path, t_list *list);
char *ft_make_path(char **path, t_list *list);
int ft_nextpipe(char **path, t_list *list);
int ft_stdout(char **path, t_list *list);
int ft_stdin(char **path, t_list *list);
int ft_distributor(char **path, t_list *list);
void ft_pwd(char *full_path, t_list *list);
int ft_empty(char **path, t_list *list);
char **ft_env(char **en);
void ft_cd(char *full_path, t_list *list);
#endif