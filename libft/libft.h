#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>

void		ft_bzero1(int *s, size_t n);
void		ft_bzero(void *s, size_t n);
long		ft_atoi(const char *str);
int			ft_strlen(char *str);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
char		*ft_strdup(char *s1);
int			ft_strncmp(const char *ss1, const char *ss2, size_t n);
void		*ft_memset(void *destination, int c, size_t n);
void		*ft_memcpy(void *destination, const void *source, size_t n);
void		*ft_memccpy(void *destination, const void *source, int c, size_t n);
void		*ft_memmove(void *destination, const void *source, size_t n);
void		*ft_memchr(const void *arr, int c, size_t n);
int			ft_memcmp(const void *arr1, const void *arr2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c );
char		*ft_strchr(const char *str, int ch);
char		*ft_strrchr(const char *str, int ch);
char		*ft_strnstr(const char *big, const char *little, size_t length);
void		*ft_calloc(size_t number, size_t size );
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_export(char *s1, char *s2);
char		*ft_strjoin_cd(char const *s1, char const *s2);
int			ft_strlen_g(const char *str);
int			ft_strcmp(const char *ss1, const char *ss2);

typedef struct s_redirect
{
	int					flag;
	char				*filename;
	int					flag_for_stdout;
	int					flag_for_stdin;
	int					flag_for_strange;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_list
{
	t_redirect		*head_redirect;
	char			**cmd;
	char			**env;
	int				flag_for_pipe;
	int				fd0;
	int				fd1;
	int				flag_for_job;
	char			*filename_for_job;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(char **content, char **envpe);
t_redirect	*ft_lstnew_redirect(int flag, char *name);
void		ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstprelast(t_list *lst);
t_redirect	*ft_lstlast_redirect(t_redirect *lst);
t_redirect	*ft_lstprelast_redirect(t_redirect *lst);
void		ft_lstclear_redirect(t_redirect **lst, void (*del)(void *));
char		*ft_strjoin_pars(char *s1, char *s2);
int			ft_lstsize_redirect(t_redirect *lst);

#endif
