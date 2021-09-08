#include "minishell.h"

int	ft_strcmp(const char *ss1, const char *ss2)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)ss1;
	s2 = (unsigned char *)ss2;
	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

int	ft_strncmp(const char *ss1, const char *ss2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)ss1;
	s2 = (unsigned char *)ss2;
	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' && s2[i] != '\0') && (s1[i] == s2[i] && i < n - 1))
		i++;
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}



// int	main(void)
// {
// 	char *s1 = "_=/Users/blessed/Desktop/minishell/./mini";
// 	char *s2 = "_";
// 	printf("sys: %d my: %d\n", strncmp(s1, s2, strlen(s2)), ft_strncmp(s1, s2, strlen(s2)));
// 	return (0);
// }
