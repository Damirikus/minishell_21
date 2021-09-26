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
#include "get_next_line.h"
# define RED "\x1B[31m"
# define WHITE "\x1B[37m"

int code_exit;

char **ft_path(char *str);
void ft_echo(char *full_path, t_list *list);
int ft_pipe(char **path, t_list *list);
char *ft_make_path(char **path, t_list *list);
int ft_stdout(char **path, t_list *list, t_redirect *current);
int ft_stdin(char **path, t_list *list, t_redirect *current);
int ft_distributor(char **path, t_list *list, int len);
void ft_pwd(char *full_path, t_list *list);

void ft_cd(char *full_path, t_list *list, int len);
void ft_exit(t_list *list, int len);
int ft_redirections(t_list *list, char **path);
int ft_first_variation(t_list *list, char **path);
int ft_second_variation(t_list *list, char **path);
//char **ft_creat_all_key(t_list *list);
// int ft_stdin_key(char **key);
int ft_stdin_key(char **key, t_list *list);
int ft_stdin_stdout(t_list *list, char **path, t_redirect *pstdin, t_redirect *pstdout);
int ft_fourth_variation(t_list *list, char **path);
int ft_write_third_stdin(char **key);
int ft_third_variation(t_list *list, char **path);
int ft_fifth_variation(t_list *list, char **path);
t_redirect *ft_chek_files_fifth(t_list *list, char **path);
int ft_chek_all_files(t_list *list);
void ft_pipe_redirect(void);
int ft_pipe_redirect_out(char **path, t_list *list);
int ft_pipe_redirect_outout(char **path, t_list *list);
int	ft_check_max_min(char *str);
int ft_exit_redirect(t_list *list);
int ft_open_pipe(t_list *list);
int ft_key_handler(t_list *list, t_redirect *redirect);
int ft_creat_chek_files(t_list *list, t_redirect *redirect);
int ft_realization(t_list *list, char **path, int len);
int ft_find_home(t_list *list);
#endif



/*


*/