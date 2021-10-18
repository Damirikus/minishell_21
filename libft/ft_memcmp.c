/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:11 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:12 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	unsigned char	*rr1;
	unsigned char	*rr2;
	size_t			i;

	rr1 = (unsigned char *)arr1;
	rr2 = (unsigned char *)arr2;
	i = 0;
	while (n--)
	{
		if (rr1[i] != rr2[i])
			return (rr1[i] - rr2[i]);
		i++;
	}
	return (0);
}
