/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:18:11 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/15 23:47:29 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_remove_door(t_game *g, int x, int y)
{
	size_t	i;

	if ((g->map.map[y][x + 1] == '1' && g->map.map[y][x - 1] == '1')
		|| (g->map.map[y + 1][x] == '1' && g->map.map[y - 1][x] == '1'))
		return ;
	g->map.map[y][x] = '0';
	i = 0;
	while (i < g->doors.index)
	{
		if (g->doors.u_ptr.d[i].pos.x == x && g->doors.u_ptr.d[i].pos.y == y)
		{
			g->doors.u_ptr.d[i].delete = true;
			return ;
		}
		++i;
	}
}

char	ft_get_block(t_game *g)
{
	const int	blocks[2] = {'1', 't'};

	return (blocks[g->p.weapon.state]);
}
