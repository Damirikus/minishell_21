/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:47 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:48 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_front(const char *sf, char *setf, int lenf2);
int	ft_back(const char *sb, char *setb, int len1);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		front;
	int		back;
	char	*str;
	int		sum;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	front = ft_front(s1, (char *)set, ft_strlen((char *)set));
	back = ft_back(s1, (char *)set, ft_strlen((char *)s1));
	sum = (ft_strlen((char *)s1) - (front + back));
	if (sum < 0)
		sum = 0;
	str = (char *)malloc(sum + 1);
	if (!str)
		return (NULL);
	if (sum == 0)
	{
		str[sum] = '\0';
		return (str);
	}
	ft_strlcpy(str, s1 + front, ((size_t)sum + 1));
	return (str);
}

int	ft_front(const char *sf, char *setf, int lenf2)
{
	int	k;
	int	i;
	int	count;

	i = 0;
	while (sf[i] != '\0')
	{
		k = 0;
		count = 0;
		while (k < lenf2)
		{
			if (sf[i] != setf[k])
				count++;
			k++;
		}
		if (count == lenf2)
			return (i);
		i++;
	}
	return (i);
}

int	ft_back(const char *sb, char *setb, int len1)
{
	int	k;
	int	i;
	int	count;

	i = 0;
	while (len1 > 0)
	{
		k = 0;
		count = 0;
		while (k < ft_strlen((char *)setb))
		{
			if (sb[len1 - 1] != setb[k])
				count++;
			k++;
		}
		if (count == ft_strlen((char *)setb))
			return (i);
		len1--;
		i++;
	}
	return (i);
}
