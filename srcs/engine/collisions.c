/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:35:45 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/25 00:28:53 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_check_doors(t_game *g, const double x, const double y)
{
	size_t	i;

	i = 0;
	while (i < g->doors.index)
	{
		if (!g->doors.u_ptr.d[i].delete && g->doors.u_ptr.d[i].state != OPEN
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
		if (!g->sprites.u_ptr.s[i].delete && g->sprites.u_ptr.s[i].collision
			&& sqrt((pow(g->p.pos.x + x - g->sprites.u_ptr.s[i].pos.x, 2.0)
					+ pow(g->p.pos.y + y - g->sprites.u_ptr.s[i].pos.y,
						2.0))) < 0.5 / g->sprites.u_ptr.s[i].hr)
			return (true);
		++i;
	}
	return (false);
}

static inline void	ft_rotate_cam(t_game *g, const t_vec dir, const t_vec plane)
{
	g->p.dir = dir;
	g->p.p = plane;
}

static inline int	ft_is_teleporter(t_game *g, const int y, const int x)
{
	t_intvec	vec;

	vec = ft_get_facing_int(g->pl.side, g->pl.pos);
	if (g->pl.side && g->pr.side && vec.x == (int)g->p.pos.x
		&& vec.y == (int)g->p.pos.y && g->pl.pos.x == x && g->pl.pos.y == y)
	{
		vec = ft_get_facing_int(g->pr.side, g->pr.pos);
		g->p.pos.x = vec.x + 0.5;
		g->p.pos.y = vec.y + 0.5;
		ft_rotate_cam(g, ft_side_to_dir(g->pr.side),
			ft_side_to_plane(g->pr.side));
		return (1);
	}
	vec = ft_get_facing_int(g->pr.side, g->pr.pos);
	if (g->pl.side && g->pr.side && vec.x == (int)g->p.pos.x
		&& vec.y == (int)g->p.pos.y && g->pr.pos.x == x && g->pr.pos.y == y)
	{
		vec = ft_get_facing_int(g->pl.side, g->pl.pos);
		g->p.pos.x = vec.x + 0.5;
		g->p.pos.y = vec.y + 0.5;
		ft_rotate_cam(g, ft_side_to_dir(g->pl.side),
			ft_side_to_plane(g->pl.side));
		return (2);
	}
	return (0);
}

static inline bool	ft_teleport(t_game *g, const double x, const double y)
{
	if (x < 0.0 && ft_is_teleporter(g, (int)(g->p.pos.y + y), (int)((g->p.pos.x
			+ x) - 0.1)))
		return (true);
	if (x > 0.0 && ft_is_teleporter(g, (int)(g->p.pos.y + y), (int)((g->p.pos.x
			+ x) + 0.1)))
		return (true);
	if (y < 0.0 && ft_is_teleporter(g, (int)((g->p.pos.y + y) - 0.1),
		(int)(g->p.pos.x + x)))
		return (true);
	if (y > 0.0 && ft_is_teleporter(g, (int)((g->p.pos.y + y) + 0.1),
		(int)(g->p.pos.x + x)))
		return (true);
	return (false);
}

bool	ft_can_move(t_game *g, const double x, const double y)
{
	if (ft_teleport(g, x, y))
		return (true);
	if ((g->p.pos.x + x) <= 1.1 || (g->p.pos.x + x) >= g->w - 1.1 || (g->p.pos.y
			+ y) <= 1.1 || (g->p.pos.y + y) >= g->length - 1.1)
		return (false);
	if (g->noclip)
		return (true);
	if (x < 0.0 && ic("1eryuiopadfghjklzxtwj", g->m.m[(int)(g->p.pos.y
				+ y)][(int)((g->p.pos.x + x) - 0.1)]))
		return (false);
	if (x > 0.0 && ic("1eryuiopadfghjklzxtwj", g->m.m[(int)(g->p.pos.y
				+ y)][(int)((g->p.pos.x + x) + 0.1)]))
		return (false);
	if (y < 0.0 && ic("1eryuiopadfghjklzxtwj", g->m.m[(int)((g->p.pos.y + y)
				- 0.1)][(int)(g->p.pos.x + x)]))
		return (false);
	if (y > 0.0 && ic("1eryuiopadfghjklzxtwj", g->m.m[(int)((g->p.pos.y + y)
				+ 0.1)][(int)(g->p.pos.x + x)]))
		return (false);
	if (ft_check_doors(g, x, y))
		return (false);
	return (true);
}
