/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:36:48 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/26 15:10:55 by wouhliss         ###   ########.fr       */
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
	if (r->side == -1)
		r->id = 3;
	else if (r->side == -2)
		r->id = 2;
	else if (r->side == 1)
		r->id = 1;
	else if (r->side == 2)
		r->id = 0;
	return (val);
}

inline void	ft_wall(t_game *game)
{
	double	wallx;

	wallx = get_wall_x(game, &game->r);
	game->r.tex.x = get_tex_x(&game->r, wallx);
	game->r.mystep = (double)game->r.twidth / game->r.line_height;
	game->r.texpos = (game->r.draw.x - HALF_HEIGHT + game->r.line_height / 2
			- game->p.y) * game->r.mystep;
}

inline void	ft_drawpixel(t_game *game, int x, int y)
{
	int		color;
	// int		*rgb;

	game->r.tex.y = (int)game->r.texpos & (game->r.twidth - 1);
	game->r.texpos += game->r.mystep;
	color = ((int *)game->textures[game->r.id].addr)[game->r.twidth
		* game->r.tex.y + game->r.tex.x];
	my_mlx_pixel_put(&game->screen, x, y, color);
}
