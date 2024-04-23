/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:36:48 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/23 12:31:17 by wouhliss         ###   ########.fr       */
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

static inline int	get_tex_x(t_render *r, const double wallx, const int tw)
{
	int	val;

	val = (wallx * tw);
	if (r->side < 0 && r->ray_dir.x > 0)
		val = tw - val - 1;
	if (r->side > 1 && r->ray_dir.y > 0)
		val = tw - val - 1;
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
	r->tex.x = get_tex_x(r, wallx, r->twidth);
	r->linetex.x = get_tex_x(r, wallx, 64);
	r->mystep = (double)r->twidth / r->lh;
	r->linestep = (double)64 / r->lh;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->mystep;
	r->linepos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->linestep;
}

void	ft_drawwallpixel(t_game *game, const int x, const int y, t_render *r)
{
	unsigned int	color;

	r->tex.y = (int)(r->texpos) & (r->twidth - 1);
	r->texpos += r->mystep;
	r->linetex.y = (int)r->linepos & (63);
	r->linepos += r->linestep;
	color = ((int *)game->wt[r->id].a)[r->s + r->twidth * r->tex.y + r->tex.x];
	if (game->p.looking && game->p.look_pos.x == r->map.x
		&& game->p.look_pos.y == r->map.y && (!r->linetex.y
			|| r->linetex.y == 63 || !r->linetex.x || r->linetex.x == 63))
	{
		color = 0x00FF0000;
		*(((unsigned int *)game->s.a) + (y * W) + x) = color;
		return ;
	}
	if (*(((unsigned int *)game->s.a) + (y * W) + x) != color)
		*(((unsigned int *)game->s.a) + (y * W) + x) = color;
}
