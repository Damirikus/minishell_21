/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:07 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:08 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	char	*dd;
	char	*ss;
	char	sym;

	sym = (char)c;
	dd = (char *)destination;
	ss = (char *)source;
	if (!source && !destination)
		return (destination);
	while (n--)
	{
		*dd = *ss;
		if (*ss == sym)
			return ((void *)dd + 1);
		dd++;
		ss++;
	}
	return (NULL);
}
