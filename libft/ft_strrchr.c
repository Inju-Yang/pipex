/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 14:28:45 by inyang            #+#    #+#             */
/*   Updated: 2020/10/08 15:58:18 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	char	a;
	int		i;
	int		len;

	s = (char *)str;
	a = (char)c;
	len = 0;
	while (s[len])
		len++;
	i = len;
	while (i >= 0)
	{
		if (s[i] == a)
			return (s + i);
		i--;
	}
	return (0);
}
