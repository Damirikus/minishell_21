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
#include <ctype.h>
#include <dirent.h>
#include "get_next_line.h"
# define RED "\x1B[31m"
# define WHITE "\x1B[37m"


typedef struct	s_env
{
	int				sys;
	char			*content;
	struct s_env	*next;
}				t_env;

int f;

typedef struct s_data
{
	t_list *head_command;
	int len;
	char **path;
	int flat;
	int a[2];
	int b[2];
	int fd_mother;

	int td[2];
	void *sg;
	/* Env && export */
	t_env	*head_env;
	char	*current_pwd;
	char	*current_oldpwd;
	char	**original_env;
	char	**current_env;
	char	**execve_env;
	char	**current_export;

	int code_exit;

} t_data;

/* SIGNAL */
void    rl_replace_line(const char *buffer, int val);
void ft_ctrlc(int signal);
void ft_ctrl(int signal);
void ft_hz(int sig);


char **ft_path(char *str);
int ft_pipe(char **path, t_list *list);
char *ft_make_path(char **path, t_list *list);
int ft_distributor(t_list *list, t_data *data);
void ft_distributor_part(t_list *list, t_data *data, char *full_path);
int ft_realization(t_list *list, t_data *data);
void ft_realization_mother(t_list *list, t_data *data);
int ft_realization_part(t_list *list, t_data *data);
void ft_realization_daughter(t_list *list, t_data *data);
void	ft_realization_daughter_part2(t_list *list, t_data *data);
void ft_closer(t_list *list);
void ft_check_bild_func(t_list *list, t_data *data);

/* REDIRECTS */
int ft_chek_all_files(t_list *list, t_data *data);
int ft_key_handler(t_list *list, t_redirect *redirect, t_data *data);
int ft_creat_chek_files(t_list *list, t_redirect *redirect, t_data *data);
int ft_stdout(t_list *list, t_redirect *redirect);
int ft_stdoutout(t_list *list, t_redirect *redirect);
int ft_stdin(t_list *list, t_redirect *redirect);
int	ft_key_handler_2(void *sg, t_redirect *redirect);
int ft_key_handler_3(t_redirect *redirect, t_data *data);
int ft_key_handler_3_part(char *str, t_data *data);
int ft_key_handler_creat(t_list *list, t_data *data);

/* build commands */
/* echo */
void ft_echo(t_list *list);
void ft_echo_part(t_list *list, int i, int qw);
void ft_echo_part2(t_list *list, int i, int qw);
int ft_echo_part_null(t_list *list, int k, int qw);
/* pwd */
void ft_pwd(void);
/* ft_cd */
int ft_cd(t_list *list, t_data *data);
int ft_cd_part(t_list *list, t_data *data);
int ft_find_home(t_list *list, t_data *data);
void ft_find_home_part(t_list *list, t_data *data, int i);
int ft_cd_part_last(t_list *list, t_data *data);
/* exit */
int ft_exit_part(long code, t_list *list, int len, t_data *data);
int ft_exit_part2(t_data *data);
void ft_exit(t_list *list, int len, t_data *data);
int	ft_check_max_min(char *str);
int ft_exit_inner_part( t_list *list, int i, int len, t_data *data);
void ft_exit_part_inner(t_list *list, t_data *data, int len);
int ft_exit_exit(t_data *data, int len, long code);




/* Aslan utils */
char	*add_quotes(char *str);

/*      LIST   Aslan env       */
void	print_list_env(t_env *head);
t_env	*ft_lstnew_initial_env(char *content);
t_env	*ft_lstnew_export_env(char *content);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_lstsize_env(t_env *lst);


/*      ENV          */
void	env_to_list(t_data *shell);
int		both_are_sys(t_data *shell, int i);
void	list_to_2D_massive_env(t_data *shell);
void	list_to_2D_massive_export(t_data *shell);
void	list_to_2D_massive_env_execve(t_data *shell);
void	ft_free_for_export(t_data *shell);
void	ft_free_for_env(t_data *shell);
void	list_to_2D_massive_export_sort_sys(t_data *shell);
void	print_list_env1(t_env *head);
void	print_2d_massive(char **mass, t_list *list, t_data *data);
void	unset_env(t_data *shell, char *key);
void	export_env(t_data *shell, char *string);
int		export_env_variable_strong(char *string);
int		export_env_variable_present(t_data *shell, char *str);
void	renew_env_export_massive(t_data *shell);
int		ft_strlen_key(char *str);
void	ft_unset(t_data *data, t_list *list);
void	ft_export(t_data *data, t_list *list);
int		check_name_unset(char *str, t_data *data);
int		check_name_export(char *str, t_data *data);
void	pwd_oldpwd_remaker(t_data *data);
void	renew_pwd_oldpwd(t_data *data);
void	shlvl_plus(t_data *data);
int		list_to_2D_massive_env_len(t_data *shell);
void	export_env_append(t_data *shell, char *string);
t_env	*export_env_append_tmp(t_data *shell, char *clean_string);
char	*clean_string_export(char *string);
int		export_env_variable_strong(char *string);
int		export_env_variable_present(t_data *shell, char *str);
void	pwd_remaker(t_data *data);

/* prepars && pars */
int		ft_error(int code, t_data *data);
int		preparser(char *str, t_data *data);
int		check_quotes(char *str, int *i, t_data *data);
int		check_pipe_redir(char *str, int *i, t_data *data);
int		check_quotes_skip(char *str, int *i, int code, t_data *data);
int		check_pipe(char *str, int *i, t_data *data);
int		check_redir(char *str, int *i, t_data *data);
t_list	*parser(char *str, t_data *data);

/* SPLIT BY PIPE */
char	**ft_split_by_pipe(char *str);
char	*ft_cutstr(char *str, int start, int finish);
void	ft_skip_quotes(char *str, int *i);



/* DOLLAR PULL  */
void	dollar_pull(char **pipe_mass, t_data *data);
void	dollar_pull_for_redirect(t_list *head_command, t_data *data);
void	dollar_pull_swaper(char **pipe_mass, int number, char *value, int start);
void	dollar_pull_swaper_redirect(char **str, char *value, int start);
void	dollar_cut_from_str(char **pipe_mass, int number, int start, int finish);
void	dollar_cut_from_str_redirect(char **str, int start, int finish);
char	*dollar_pull_helper_value_maker_redirect(char *tmp, int start, int *j, t_data *data);
int		ft_isalnum_strong(char c, int flag);

/*	REDIRECT CUTTER	*/
void	redirect_parser(char **pipe_mass, t_list **head_command);
void	create_new_command_list(char **pipe_mass, t_list **head_command, int number);
void	add_redirect(char *str, t_list *tmp, int *i);
void	redirect_cut_from_str(char **pipe_mass);
void	redirect_cutter(char **pipe_mass, int number, int i);
void	redirect_flag_putter(t_list *list);
void	pipe_flag_putter(t_list **head_command);


/*	COMAND MAKER	*/
void	cmd_maker(char **pipe_mass, t_list **head_command);

/*	QUOTES KILLER	*/
void	quotes_killer(t_list **head_command);
void	quotes_killer_command(t_list *head_command);
int		quotes_killer_result_len(char *name);
void	quotes_killer_result_len_skip(char *name, int *i, int *result);

/*	COMMAND LIST FREE */
void	list_free_redirect(t_redirect **redirect);
void	list_free_command(t_list **head);
void	list_free(t_list **head);

void	ft_print_list(t_list *head_command);


/*	FREE WHOLE PROJECT	*/
void	free_whole_project(t_data *data);
void	ft_free_path(t_data *data);

void ft_print_all(t_data *data);
#endif



/*
*/


















// #ifndef MINISHELL_H
// #define MINISHELL_H

// #include "./libft/libft.h"
// # include <signal.h>
// # include <fcntl.h>
// # include <stdint.h>
// # include <limits.h>
// # include <time.h>
// # include <stdbool.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <errno.h>
// #include <ctype.h>
// #include <dirent.h>
// #include "get_next_line.h"
// # define RED "\x1B[31m"
// # define WHITE "\x1B[37m"


// typedef struct	s_env
// {
// 	int				sys;
// 	char			*content;
// 	struct s_env	*next;
// }				t_env;

// int f;

// typedef struct s_data
// {
// 	t_list *head_command;
// 	int len;
// 	char **path;
// 	int flat;
// 	int a[2];
// 	int b[2];
// 	int fd_mother;

// 	int td[2];
// 	void *sg;
// 	/* Env && export */
// 	t_env	*head_env;
// 	char	*current_pwd;
// 	char	*current_oldpwd;
// 	char	**original_env;
// 	char	**current_env;
// 	char	**execve_env;
// 	char	**current_export;

// 	int code_exit;

// } t_data;

// /* SIGNAL */
// void    rl_replace_line(const char *buffer, int val);
// void ft_ctrlc(int signal);
// void ft_ctrl(int signal);
// void ft_hz(int sig);


// char **ft_path(char *str);
// int ft_pipe(char **path, t_list *list);
// char *ft_make_path(char **path, t_list *list);
// int ft_distributor(t_list *list, t_data *data);
// void ft_distributor_part(t_list *list, t_data *data, char *full_path);
// int ft_realization(t_list *list, t_data *data);



// /* REDIRECTS */
// int ft_chek_all_files(t_list *list, t_data *data);
// int ft_key_handler(t_list *list, t_redirect *redirect, t_data *data);
// int ft_creat_chek_files(t_list *list, t_redirect *redirect, t_data *data);
// int ft_stdout(t_list *list, t_redirect *redirect);
// int ft_stdoutout(t_list *list, t_redirect *redirect);
// int ft_stdin(t_list *list, t_redirect *redirect);
// int	ft_key_handler_2(char **str, void *sg, t_redirect *redirect);
// int ft_key_handler_creat(t_list *list, t_data *data);

// /* build commands */
// /* echo */
// void ft_echo(t_list *list);
// void ft_echo_part(t_list *list, int i, int qw);
// void ft_echo_part2(t_list *list, int i, int qw);
// /* pwd */
// void ft_pwd(void);
// /* ft_cd */
// int ft_cd(t_list *list, t_data *data);
// int ft_cd_part(t_list *list, t_data *data);
// int ft_find_home(t_list *list, t_data *data);
// /* exit */
// void ft_exit_part(long code, t_list *list, int len, t_data *data);
// void ft_exit(t_list *list, int len, t_data *data);
// int	ft_check_max_min(char *str);
// int ft_exit_inner_part( t_list *list, int i, int len, t_data *data);




// /* Aslan utils */
// char	*add_quotes(char *str);

// /*      LIST   Aslan env       */
// t_env	*ft_lstnew_initial_env(char *content);
// t_env	*ft_lstnew_export_env(char *content);
// void	ft_lstadd_back_env(t_env **lst, t_env *new);
// t_env	*ft_lstlast_env(t_env *lst);
// int		ft_lstsize_env(t_env *lst);


// /*      ENV          */
// void	env_to_list(t_data *shell);
// int		both_are_sys(t_data *shell, int i);
// void	list_to_2D_massive_env(t_data *shell);
// void	list_to_2D_massive_export(t_data *shell);
// void	list_to_2D_massive_env_execve(t_data *shell);
// void	ft_free_for_export(t_data *shell);
// void	ft_free_for_env(t_data *shell);
// void	list_to_2D_massive_export_sort_sys(t_data *shell);
// void	print_list_env1(t_env *head);
// void	print_2d_massive(char **mass, t_list *list, t_data *data);
// void	unset_env(t_data *shell, char *key);
// void	export_env(t_data *shell, char *string);
// int		export_env_variable_strong(char *string);
// int		export_env_variable_present(t_data *shell, char *str);
// void	renew_env_export_massive(t_data *shell);
// int		ft_strlen_key(char *str);
// void	ft_unset(t_data *data, t_list *list);
// void	ft_export(t_data *data, t_list *list);
// int		check_name_unset(char *str, t_data *data);
// int		check_name_export(char *str, t_data *data);
// void	pwd_oldpwd_remaker(t_data *data);
// void	renew_pwd_oldpwd(t_data *data);
// void	shlvl_plus(t_data *data);
// int		list_to_2D_massive_env_len(t_data *shell);
// void	export_env_append(t_data *shell, char *string);
// t_env	*export_env_append_tmp(t_data *shell, char *clean_string);
// char	*clean_string_export(char *string);
// int		export_env_variable_strong(char *string);
// int		export_env_variable_present(t_data *shell, char *str);
// void	pwd_remaker(t_data *data);

// /* prepars && pars */
// int		ft_error(int code, t_data *data);
// int		preparser(char *str, t_data *data);
// int		check_quotes(char *str, int *i, t_data *data);
// int		check_pipe_redir(char *str, int *i, t_data *data);
// int		check_quotes_skip(char *str, int *i, int code, t_data *data);
// int		check_pipe(char *str, int *i, t_data *data);
// int		check_redir(char *str, int *i, t_data *data);
// t_list	*parser(char *str, t_data *data);

// /* SPLIT BY PIPE */
// char	**ft_split_by_pipe(char *str);
// char	*ft_cutstr(char *str, int start, int finish);
// void	ft_skip_quotes(char *str, int *i);



// /* DOLLAR PULL  */
// void	dollar_pull(char **pipe_mass, t_data *data);
// void	dollar_pull_for_redirect(t_list *head_command, t_data *data);
// void	dollar_pull_swaper(char **pipe_mass, int number, char *value, int start);
// void	dollar_pull_swaper_redirect(char **str, char *value, int start);
// void	dollar_cut_from_str(char **pipe_mass, int number, int start, int finish);
// void	dollar_cut_from_str_redirect(char **str, int start, int finish);
// char	*dollar_pull_helper_value_maker_redirect(char *tmp, int start, int *j, t_data *data);
// int		ft_isalnum_strong(char c, int flag);

// /*	REDIRECT CUTTER	*/
// void	redirect_parser(char **pipe_mass, t_list **head_command);
// void	create_new_command_list(char **pipe_mass, t_list **head_command, int number);
// void	add_redirect(char *str, t_list *tmp, int *i);
// void	redirect_cut_from_str(char **pipe_mass);
// void	redirect_cutter(char **pipe_mass, int number, int i);
// void	redirect_flag_putter(t_list *list);
// void	pipe_flag_putter(t_list **head_command);


// /*	COMAND MAKER	*/
// void	cmd_maker(char **pipe_mass, t_list **head_command);

// /*	QUOTES KILLER	*/
// void	quotes_killer(t_list **head_command);
// void	quotes_killer_command(t_list *head_command);
// int		quotes_killer_result_len(char *name);
// void	quotes_killer_result_len_skip(char *name, int *i, int *result);

// /*	COMMAND LIST FREE */
// void	list_free_redirect(t_redirect **redirect);
// void	list_free_command(t_list **head);
// void	list_free(t_list **head);

// void	ft_print_list(t_list *head_command);


// /*	FREE WHOLE PROJECT	*/
// void	free_whole_project(t_data *data);
// void	ft_free_path(t_data *data);

// void ft_print_all(t_data *data);
// #endif



// /*


// */
