/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:32:26 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/20 23:48:45 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		++i;
	while (s[--i])
	{
		if (s[i] == c)
			return (s + i);
	}
	if (s[i] == c)
		return (s + i);
	return (NULL);
}

int	ft_strlen(const char *str)
{
	const char	*s;

	if (!str)
		return (0);
	s = str;
	while (*s)
		++s;
	return (s - str);
}

char	**ft_copy(char **map)
{
	char	**copied;
	int		i;

	i = 0;
	copied = malloc(sizeof(char *) * (plen(map) + 1));
	if (!copied)
	{
		panic(MALLOC_ERR);
		return (NULL);
	}
	while (i < plen(map))
	{
		copied[i] = ft_strdup(map[i]);
		i++;
	}
	copied[i] = NULL;
	return (copied);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (*s1 - *s2);
	while (*s1 && *s1 == *s2 && --n)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
