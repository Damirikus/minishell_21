/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:12 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:13 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	char	*rr;
	char	*oo;

	rr = (char *)destination;
	oo = (char *)source;
	if (!source && !destination)
		return (destination);
	while (n--)
		*rr++ = *oo++;
	return (destination);
}
