/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:36:48 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/13 11:12:30 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline double	get_wall_x(t_render *r)
{
	double	wallx;

	if (r->side < 0)
		wallx = r->pos.y + r->pdist * r->ray_dir.y;
	else
		wallx = r->pos.x + r->pdist * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

static inline int	get_tex_x(t_render *r, const double wallx)
{
	int	val;

	val = (wallx * r->twidth);
	if (r->side < 0 && r->ray_dir.x > 0)
		val = r->twidth - val - 1;
	if (r->side > 1 && r->ray_dir.y > 0)
		val = r->twidth - val - 1;
	return (val);
}

void	ft_wall(const t_game *game, t_render *r)
{
	double	wallx;

	if (r->side == -1)
		r->id = TEA;
	else if (r->side == -2)
		r->id = TWE;
	else if (r->side == 1)
		r->id = TSO;
	else if (r->side == 2)
		r->id = TNO;
	r->twidth = game->wt[r->id].width;
	r->s = game->wt[r->id].s;
	wallx = get_wall_x(r);
	r->tex.x = get_tex_x(r, wallx);
	r->mystep = (double)r->twidth / r->lh;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->mystep;
}

void	ft_drawwallpixel(t_game *game, const int x, const int y,
		t_render *r)
{
	int	color;

	if (r->hit == 2 && r->tex.x > r->twidth * (1 - r->shift))
		return ;
	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	color = ((int *)game->wt[r->id].addr)[r->s + r->twidth * r->tex.y
		+ r->tex.x];
	if (r->hit == 2)
	{
		game->zbuffer[x][y] = r->pdist;
		color = ((int *)game->wt[r->id].addr)[r->s + r->twidth * r->tex.y
		+ r->tex.x + (int)(r->twidth * r->shift)];
	}
	if (game->p.looking && game->p.look_pos.x == r->map.x
		&& game->p.look_pos.y == r->map.y && (!r->tex.y || r->tex.y == r->twidth
			- 1 || !r->tex.x || r->tex.x == r->twidth - 1))
		color = 0x00FF0000;
	*(((unsigned int *)game->screen.addr) + (y * WIDTH) + x) = color;
}
