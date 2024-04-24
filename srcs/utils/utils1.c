/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:49:36 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 19:55:43 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		++s;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		++i;
	}
	res[i] = 0;
	return (res);
}

int	plen(char **m)
{
	int	i;

	if (!m || !(*m))
		return (0);
	i = 0;
	while (m[i])
		++i;
	return (i);
}

char	**join_tab(char **m, char *str)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (plen(m) + 2));
	if (!res)
		return (NULL);
	if (!m || !(*m))
	{
		res[0] = str;
		res[1] = NULL;
		return (res);
	}
	i = 0;
	while (m[i])
	{
		res[i] = m[i];
		i++;
	}
	res[i++] = str;
	res[i] = NULL;
	return (res);
}
