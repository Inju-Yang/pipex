/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 23:44:56 by yang              #+#    #+#             */
/*   Updated: 2020/10/09 21:04:01 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*set_dst;
	unsigned char	*set_src;
	size_t			i;

	if (dst == 0 && src == 0)
		return (0);
	set_dst = dst;
	set_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		set_dst[i] = set_src[i];
		i++;
	}
	return (dst);
}
