/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:36:07 by inyang            #+#    #+#             */
/*   Updated: 2020/10/23 15:27:30 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	result;
	int		i;
	int		j;

	dst_len = ft_strlen(dst);
	result = ft_strlen(src);
	i = 0;
	j = dst_len;
	while ((src[i] != '\0') && i < (int)(size - dst_len - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	if (size < dst_len)
		result += size;
	else
		result += dst_len;
	return (result);
}
