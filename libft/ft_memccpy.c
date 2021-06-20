/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 00:33:10 by yang              #+#    #+#             */
/*   Updated: 2020/10/07 20:12:21 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*new_dst;
	unsigned char	*new_src;
	size_t			i;
	unsigned char	a;

	new_dst = dst;
	new_src = (unsigned char *)src;
	a = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		new_dst[i] = new_src[i];
		if (new_src[i] == a)
			return (dst + i + 1);
		i++;
	}
	return (0);
}
