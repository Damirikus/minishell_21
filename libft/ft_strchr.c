/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:27 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:28 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*str2;

	str2 = (char *)str;
	while (*str2 != '\0')
	{
		if (*str2 == ch)
			return (str2);
		str2++;
	}
	if (*str2 == ch)
		return (str2);
	return (NULL);
}
