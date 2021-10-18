/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:30 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:31 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_pars(char *s1, char *s2)
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
