/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:29:14 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 00:40:54 by wouhliss         ###   ########.fr       */
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

void	ft_portal(const t_game *game, t_render *r)
{
	double	wallx;

	r->id = r->hit - 4;
	r->twidth = game->ptextures[r->id].width;
	r->s = game->ptextures[r->id].s;
	wallx = get_wall_x(r);
	r->tex.x = get_tex_x(r, wallx);
	r->mystep = (double)r->twidth / r->lh;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->mystep;
}

void	ft_drawppixel(t_thread *t, const int x, const int y, t_render *r)
{
	unsigned int	color;

	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	if (t->g->p.looking && t->g->p.look_pos.x == r->map.x
		&& t->g->p.look_pos.y == r->map.y && (!r->tex.y || r->tex.y == r->twidth
			- 1 || !r->tex.x || r->tex.x == r->twidth - 1))
	{
		color = 0x00FF0000;
		*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
		return ;
	}
	color = ((int *)t->g->ptextures[r->id].a)[r->s + r->twidth * r->tex.y + r->tex.x];
	if ((color & 0x00FFFFFF) != 0 && color != 65280)
	{
		t->zbuffer[x - t->dx][y] = r->pdist;
		if (*(((unsigned int *)t->g->s.a) + (y * W) + x) != color)
			*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
	}
}
