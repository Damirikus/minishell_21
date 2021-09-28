#include "preparser.h"

int	ft_strlen_g(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dd;
	int		i;
	int		j;
	int		sl1;
	int		sl2;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	sl1 = ft_strlen_g(s1);
	sl2 = ft_strlen_g(s2);
	dd = (char *)malloc(sizeof(char) * (sl1 + sl2 + 1));
	if (dd == NULL)
		return (NULL);
	while (++i < sl1)
		dd[i] = s1[i];
	while (j < sl2)
		dd[i++] = s2[j++];
	dd[i] = '\0';
	free(s1);
	return (dd);
}

t_list	*ft_lstnew(char **content, char **envpe)
{
	t_list	*begin;

	begin = (t_list *) malloc(sizeof(t_list));
	if (!begin)
		return (NULL);
	begin->cmd = content;
	begin->flag_for_pipe = 1;
	begin->fd0 = -1;
	begin->fd1 = -1;
	begin->flag_for_job = 0;
	begin->pid_mother = dup(0);
	begin->env = envpe;
	begin->next = NULL;
	begin->head_redirect = NULL;
	return (begin);
}

t_redirect	*ft_lstnew_redirect(int flag, char *name)
{
	t_redirect	*begin;

	begin = (t_redirect *) malloc(sizeof(t_redirect));
	if (!begin)
		return (NULL);
	begin->flag_for_stdin = 0;
    begin->flag_for_stdout = 0;
	if (flag == 1)
		begin->flag_for_stdout = 1;
	if (flag == 2)
		begin->flag_for_stdout = 2;
	if (flag == 3)
		begin->flag_for_stdin = 1;
	if (flag == 4)
		begin->flag_for_stdin = 2;
    begin->filename = name;
    begin->flag = 0;
    begin->next = NULL;
	return (begin);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->next = NULL;
}

void ft_lstadd_back_redirect(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_redirect(*lst);
	last->next = new;
	new->next = NULL;
}

t_list *ft_lstlast(t_list *lst)
{
	t_list *tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_list *ft_lstprelast(t_list *lst)
{
	t_list	*tmp;
	t_list	*pre;

	tmp = lst;
	pre = tmp;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (pre);
		pre = tmp;
		tmp = tmp->next;
	}
	return (pre);
}

t_redirect	*ft_lstlast_redirect(t_redirect *lst)
{
	t_redirect	*tmp;
	
	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

t_redirect	*ft_lstprelast_redirect(t_redirect *lst)
{
	t_redirect	*tmp;
	t_redirect	*pre;

	tmp = lst;
	pre = tmp;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (pre);
		pre = tmp;
		tmp = tmp->next;
	}
	return (pre);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_lstsize_redirect(t_redirect *lst)
{
	t_redirect	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstclear_redirect(t_redirect **lst, void (*del)(void *))
{
	t_redirect	*tmp;

	tmp = *lst;
	(*del)(tmp->filename);
	(*del)(tmp->next);
	free(tmp);
	*lst = NULL;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	// есть что удалит
	(*del)(tmp->next);
	free(tmp);
	*lst = NULL;
}
