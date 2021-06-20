/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 21:51:16 by inyang            #+#    #+#             */
/*   Updated: 2021/06/13 20:49:02 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cnt(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			cnt++;
		}
	}
	return (cnt);
}

static int		ft_n_malloc(char **all, size_t k, size_t cnt)
{
	if (!(all[k] = malloc(cnt + 1)))
	{
		while (k > 0)
		{
			k--;
			free(all[k]);
		}
		free(all);
		return (1);
	}
	return (0);
}

static size_t	ft_index(size_t *i, char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (s[*i] != c && s[*i])
	{
		(*i)++;
		cnt++;
	}
	return (cnt);
}

static int		ft_fill(char const *s, char c, char **all)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	size_t	cnt;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		cnt = ft_index(&i, s, c);
		if (ft_n_malloc(all, k, cnt))
			return (1);
		l = 0;
		j = i - cnt;
		while (j < i)
			all[k][l++] = (char)s[j++];
		all[k++][l] = '\0';
	}
	return (0);
}

char			**ft_split(char const *s, char c)
{
	size_t	len;
	char	**all;

	if (!s)
		return (NULL);
	len = ft_cnt(s, c);
	if (!(all = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	if (ft_fill(s, c, all))
		return (NULL);
	all[len] = NULL;
	return (all);
}
