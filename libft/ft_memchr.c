/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:09 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:10 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	char	*rr;
	char	sym;
	size_t	i;

	rr = (char *)arr;
	sym = (char)c;
	i = 0;
	while (n--)
	{
		if (rr[i] == sym)
			return (&rr[i]);
		i++;
	}
	return (NULL);
}
