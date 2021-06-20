/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 21:02:50 by inyang            #+#    #+#             */
/*   Updated: 2020/10/09 21:14:36 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *str, int c)
{
	char	*s;
	char	a;
	int		i;

	s = (char *)str;
	a = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (s + i);
		i++;
	}
	if (a == '\0')
		return (s + i);
	if (s == 0)
		return (s);
	return (0);
}
