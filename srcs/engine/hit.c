/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:43:32 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/13 15:03:01 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_hitcalc(const t_game *g, t_render *r, const int type)
{
	if (type)
	{
		r->delta_dist.y /= 2;
		r->delta_dist.x /= 2;
	}
	if (r->side > 0)
		r->pdist = r->side_dist.y - r->delta_dist.y;
	else
		r->pdist = r->side_dist.x - r->delta_dist.x;
	r->lh = (int)(HEIGHT / r->pdist);
	r->draw.x = -r->lh / 2 + HALF_HEIGHT + g->p.y + (int)(g->p.jump) / r->pdist;
	if (r->draw.x < 0)
		r->draw.x = 0;
	r->draw.y = r->lh / 2 + HALF_HEIGHT + g->p.y + (int)(g->p.jump) / r->pdist;
	if (r->draw.y >= HEIGHT)
		r->draw.y = HEIGHT - 1;
	if (type)
		ft_door(g, r);
	else
		ft_wall(g, r);
}

void	ft_drawhit(t_thread *t, const int x)
{
	int		y;
	size_t	i;

	i = 0;
	while (i < t->hit.index)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (t->hit.ptr.h[i].render.draw.x <= y
				&& t->hit.ptr.h[i].render.draw.y >= y
				&& t->hit.ptr.h[i].render.pdist < t->zbuffer[x - t->dx][y])
				ft_drawdoorpixel(t, x, y, &t->hit.ptr.h[i].render);
		}
		ft_drawpsprites(t, &t->g->p.pos, &t->g->p.dir);
		++i;
	}
}
