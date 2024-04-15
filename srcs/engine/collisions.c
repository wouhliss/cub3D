/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:35:45 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/15 21:36:06 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_check_doors(t_game *g, const double x, const double y)
{
	size_t	i;

	i = 0;
	while (i < g->doors.index)
	{
		if (g->doors.u_ptr.d[i].state != OPEN
			&& g->doors.u_ptr.d[i].pos.x >= (int)((g->p.pos.x + x))
			&& g->doors.u_ptr.d[i].pos.x <= (int)((g->p.pos.x + x))
			&& g->doors.u_ptr.d[i].pos.y >= (int)((g->p.pos.y + y))
			&& g->doors.u_ptr.d[i].pos.y <= (int)((g->p.pos.y + y)))
			return (true);
		++i;
	}
	i = 0;
	while (i < g->sprites.index)
	{
		if (!g->sprites.u_ptr.s[i].hide && sqrt((pow(g->p.pos.x + x
						- g->sprites.u_ptr.s[i].pos.x, 2.0) + pow(g->p.pos.y + y
						- g->sprites.u_ptr.s[i].pos.y, 2.0))) < 0.5
			/ g->sprites.u_ptr.s[i].hr)
			return (true);
		++i;
	}
	return (false);
}

bool	ft_can_move(t_game *g, const double x, const double y)
{
	if ((g->p.pos.x + x) <= 1.1 || (g->p.pos.x + x) >= g->width - 1.1
		|| (g->p.pos.y + y) <= 1.1 || (g->p.pos.y + y) >= g->length - 1.1)
		return (false);
	if (x < 0.0 && g->map.map[(int)(g->p.pos.y + y)][(int)((g->p.pos.x + x)
			- 0.1)] == '1')
		return (false);
	if (x > 0.0 && g->map.map[(int)(g->p.pos.y + y)][(int)((g->p.pos.x + x)
			+ 0.1)] == '1')
		return (false);
	if (y < 0.0 && g->map.map[(int)((g->p.pos.y + y) - 0.1)][(int)(g->p.pos.x
			+ x)] == '1')
		return (false);
	if (y > 0.0 && g->map.map[(int)((g->p.pos.y + y) + 0.1)][(int)(g->p.pos.x
			+ x)] == '1')
		return (false);
	if (ft_check_doors(g, x, y))
		return (false);
	return (true);
}
