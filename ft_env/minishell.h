#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_env
{
	int				sys;
	char			*content;
	struct s_env	*next;
}				t_env;

typedef struct	s_shell
{
	t_env	*head_env;

	char	**original_env;
	char	**current_env;
	char	**current_export;
}				t_shell;

/*      UTILS          */
char	*ft_strdup(const char *s1);
char	*ft_strjoin_export(char *s1, char *s2);
int		ft_strcmp(const char *ss1, const char *ss2);
int		ft_strncmp(const char *ss1, const char *ss2, size_t n);
int		ft_strlen_g(const char *str);
char	*add_quotes(char *str);

/*      LIST          */
void	print_list_env(t_env *head);
t_env	*ft_lstnew_initial_env(char *content);
t_env	*ft_lstnew_export_env(char *content);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
int		ft_lstsize_env(t_env *lst);

/*      ENV          */
void	env_to_list(t_shell *shell);
int		both_are_sys(t_shell *shell, int i);
void	list_to_2D_massive_env(t_shell *shell);
void	list_to_2D_massive_export(t_shell *shell);


#endif
