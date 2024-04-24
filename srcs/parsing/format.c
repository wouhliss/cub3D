/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:55:13 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 19:55:43 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	new_line(t_game *game, int i)
{
	char	*res;
	int		j;

	res = gc(ft_calloc(1, game->w + 1), ADD);
	if (!res)
		panic(MALLOC_ERR);
	j = 0;
	while (j < ft_strlen(game->m.m[i]))
	{
		if (game->m.m[i][j] == ' ')
			res[j] = '2';
		else
			res[j] = game->m.m[i][j];
		j++;
	}
	while (j < game->w)
		res[j++] = '2';
	game->m.m[i] = res;
}

void	format_line(t_game *game, int i)
{
	int	j;

	j = 0;
	while (j < game->w)
	{
		if (game->m.m[i][j] == ' ')
			game->m.m[i][j] = '2';
		j++;
	}
}

void	pre_format_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->m.m[i])
	{
		if (ft_strlen(game->m.m[i]) < game->w)
			new_line(game, i);
		else
			format_line(game, i);
		i++;
	}
}

void	format_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->m.m[i])
	{
		j = 0;
		while (game->m.m[i][j])
		{
			if (game->m.m[i][j] == '2')
				game->m.m[i][j] = '1';
			j++;
		}
		i++;
	}
}
