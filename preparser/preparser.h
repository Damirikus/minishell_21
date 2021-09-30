#ifndef PREPARSER_H
#define PREPARSER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct s_redirect
{
	int		flag;
	char	*filename;
	int		flag_for_stdout;
	int		flag_for_stdin;
	struct s_redirect *next;
} t_redirect;

typedef struct s_list
{
	t_redirect		*head_redirect;
	char			**cmd;
	char			**env;
	int				flag_for_pipe;
	int				fd0;
	int				fd1;
	int				pid_mother;
	int				flag_for_job;
	char			*filename_for_job;
	struct s_list	*next;
}					t_list;

int		ft_error(int code);
int		preparser(char *str);
void	check_quotes(char *str, int *i);
void	check_pipe_redir(char *str, int *i);
void	parser(char *str, char **env);

/* SPLIT BY PIPE */
char	**ft_split_by_pipe(char *str);
char	*ft_cutstr(char *str, int start, int finish);
void	ft_skip_quotes(char *str, int *i);


int	ft_strlen_g(const char *str);
char	*ft_strjoin(char *s1, char *s2);

/* DOLLAR PULL  */
void	dollar_pull(char **pipe_mass, char **env);

/*	LIST	*/
t_list		*ft_lstnew(char **content, char **envpe);
t_redirect	*ft_lstnew_redirect(int flag, char *name);
void		ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstprelast(t_list *lst);
t_redirect	*ft_lstlast_redirect(t_redirect *lst);
t_redirect	*ft_lstprelast_redirect(t_redirect *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstclear_redirect(t_redirect **lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
int			ft_lstsize_redirect(t_redirect *lst);


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

#endif
