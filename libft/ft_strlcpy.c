/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:59:28 by inyang            #+#    #+#             */
/*   Updated: 2020/10/09 17:47:03 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *source, size_t size)
{
	size_t	i;
	size_t	j;

	if (*dest == '\0' || *source == '\0')
		return (0);
	j = 0;
	while (source[j])
		j++;
	if (size == 0)
		return (j);
	i = 0;
	while (source[i] != '\0' && i < size - 1)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}
