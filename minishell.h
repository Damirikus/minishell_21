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

int code_exit;


typedef struct	s_env
{
	int				sys;
	char			*content;
	struct s_env	*next;
}				t_env;


typedef struct s_data
{
	t_list *head_command;
	int len;
	char **path;

	/* Env && export */
	t_env	*head_env;
	char	*current_pwd;
	char	*current_oldpwd;
	char	**original_env;
	char	**current_env;
	char	**current_export;


} t_data;


/* SIGNAL */
void    rl_replace_line(const char *buffer, int val);
void ft_ctrlc(int signal);



char **ft_path(char *str);

int ft_pipe(char **path, t_list *list);
char *ft_make_path(char **path, t_list *list);
int ft_distributor(t_list *list, t_data *data);
int ft_chek_all_files(t_list *list);
int ft_open_pipe(t_list *list);
int ft_key_handler(t_list *list, t_redirect *redirect);
int ft_creat_chek_files(t_list *list, t_redirect *redirect);
int ft_realization(t_list *list, t_data *data);
int ft_find_home(t_list *list, t_data *data);


/* build commands */
void ft_echo(t_list *list);
void ft_pwd(void);
void ft_cd(t_list *list, t_data *data);
/* exit */
void ft_exit(t_list *list, int len);
int	ft_check_max_min(char *str);





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
void	ft_free_for_export(t_data *shell);
void	ft_free_for_env(t_data *shell);
void	list_to_2D_massive_export_sort_sys(t_data *shell);
void	print_list_env1(t_env *head);
void	print_2d_massive(char **mass);
void	unset_env(t_data *shell, char *key);
void	export_env(t_data *shell, char *string);
void	renew_env_export_massive(t_data *shell);
int		ft_strlen_key(char *str);
void	ft_unset(t_data *data, t_list *list);
void	ft_export(t_data *data, t_list *list);
int		check_name_unset(char *str);
int		check_name_export(char *str);
void	pwd_oldpwd_remaker(t_data *data);
void	renew_pwd_oldpwd(t_data *data);
// void	set_current_dir_name(t_data *data);

/* prepars && pars */
int		ft_error(int code);
int		preparser(char *str);
int		check_quotes(char *str, int *i);
int		check_pipe_redir(char *str, int *i);
int		check_quotes_skip(char *str, int *i, int code);
int		check_pipe(char *str, int *i);
int		check_redir(char *str, int *i);
//void	parser(char *str, char **env);
t_list	*parser(char *str, char **env);

/* SPLIT BY PIPE */
char	**ft_split_by_pipe(char *str);
char	*ft_cutstr(char *str, int start, int finish);
void	ft_skip_quotes(char *str, int *i);



/* DOLLAR PULL  */
void	dollar_pull(char **pipe_mass, char **env);

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


void ft_print_all(t_data *data);
#endif



/*


*/
