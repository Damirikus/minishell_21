/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:26:19 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:26:20 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	void	*rr;

	rr = destination;
	i = 0;
	while (i < n)
	{
		*((char *)destination) = c;
		destination++;
		i++;
	}
	return (rr);
}
