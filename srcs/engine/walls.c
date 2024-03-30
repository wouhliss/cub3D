/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:36:48 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/30 08:40:59 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline double	get_wall_x(t_game *g, t_render *r)
{
	double	wallx;

	if (r->side < 0)
		wallx = g->p.pos.y + r->perp_dist * r->ray_dir.y;
	else
		wallx = g->p.pos.x + r->perp_dist * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

static inline int	get_tex_x(t_render *r, double wallx)
{
	int	val;

	val = (wallx * r->twidth);
	if (r->side < 0 && r->ray_dir.x > 0)
		val = r->twidth - val - 1;
	if (r->side > 1 && r->ray_dir.y > 0)
		val = r->twidth - val - 1;
	return (val);
}

inline void	ft_wall(t_game *game, t_render *r)
{
	double	wallx;

	if (r->side == -1)
		r->id = 3;
	else if (r->side == -2)
		r->id = 2;
	else if (r->side == 1)
		r->id = 1;
	else if (r->side == 2)
		r->id = 0;
	if (r->side == game->portal_l.side && r->map.x == game->portal_l.pos.x && r->map.y == game->portal_l.pos.y)
	{
		r->id = 4;
		if (game->portal_l.side && game->portal_r.side)
			r->id = 6;
	}
	else if (r->side == game->portal_r.side && r->map.x == game->portal_r.pos.x && r->map.y == game->portal_r.pos.y)
	{
		r->id = 5;
		if (game->portal_l.side && game->portal_r.side)
			r->id = 6;
	}
	r->twidth = game->textures[r->id].width;
	r->s = game->textures[r->id].s;
	wallx = get_wall_x(game, r);
	r->tex.x = get_tex_x(r, wallx);
	r->mystep = (double)r->twidth / r->line_height;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->line_height / 2
			- game->p.y) * r->mystep;
}

inline void	ft_drawpixel(t_game *game, int x, int y, t_render *r)
{
	int		color;

	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	color = ((int *)game->textures[r->id].addr)[r->s + r->twidth
		* r->tex.y + r->tex.x];
	my_mlx_pixel_put(&game->screen, x, y, color);
}
