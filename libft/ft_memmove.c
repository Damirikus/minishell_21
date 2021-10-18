/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:14 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:15 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	char	*dd;
	char	*ss;
	size_t	i;

	i = n;
	dd = (char *)destination;
	ss = (char *)source;
	if (!source && !destination)
		return (destination);
	if (source < destination)
		while (i--)
			dd[i] = ss[i];
	if (source > destination)
		while (n--)
			*dd++ = *ss++;
	return (destination);
}
