/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdominqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:25:03 by sdominqu          #+#    #+#             */
/*   Updated: 2021/10/18 23:25:04 by sdominqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size )
{
	char	*str;

	str = malloc(size * number);
	if (!str)
		return (NULL);
	ft_bzero(str, size * number);
	return ((void *)str);
}
