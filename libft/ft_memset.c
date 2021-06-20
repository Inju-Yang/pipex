/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 23:30:37 by yang              #+#    #+#             */
/*   Updated: 2020/10/07 02:37:55 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int i, size_t n)
{
	unsigned char *set_dst;
	unsigned char src;

	set_dst = (unsigned char *)dst;
	src = (unsigned char)i;
	while (n-- > 0)
		*set_dst++ = src;
	return (dst);
}
