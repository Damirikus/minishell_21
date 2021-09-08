#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_list
{
	int				sys;
	char			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_shell
{
	t_list	*head_env;

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
void	print_list(t_list *head);
t_list	*ft_lstnew_initial(char *content);
t_list	*ft_lstnew_export(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);

/*      ENV          */
void	env_to_list(t_shell *shell);
int		both_are_sys(t_shell *shell, int i);
void	list_to_2D_massive_env(t_shell *shell);
void	list_to_2D_massive_export(t_shell *shell);


#endif
