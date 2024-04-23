/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:43:32 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/23 13:28:34 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_calcdraw(const t_game *g, t_render *r, const int type)
{
	if (type == 2)
	{
		r->dd.y /= 2;
		r->dd.x /= 2;
	}
	if (r->side > 0)
		r->pdist = r->sd.y - r->dd.y;
	else
		r->pdist = r->sd.x - r->dd.x;
	r->lh = (int)(HEIGHT / r->pdist);
	r->draw.x = -r->lh / 2 + HALF_HEIGHT + g->p.y + (int)(g->p.jump) / r->pdist;
	if (r->draw.x < 0)
		r->draw.x = 0;
	r->draw.y = r->lh / 2 + HALF_HEIGHT + g->p.y + (int)(g->p.jump) / r->pdist;
	if (r->draw.y >= HEIGHT)
		r->draw.y = HEIGHT - 1;
}

void	ft_hitcalc(const t_game *g, t_render *r, const int type)
{
	ft_calcdraw(g, r, type);
	if (type == 2)
		ft_door(g, r);
	else if (type == 3)
		ft_glass(g, r);
	else if (type > 3 && type < 8)
		ft_portal(g, r);
	else if (type == 8)
		ft_truc(g, r);
	else
		ft_wall(g, r);
}

static inline void	ft_drawhitrow(t_thread *t, const int x)
{
	int		y;
	size_t	i;

	i = t->hit.index;
	while (i > 0)
	{
		--i;
		y = -1;
		while (++y < HEIGHT)
		{
			if (t->hit.u_ptr.h[i].render.draw.x > y
				|| t->hit.u_ptr.h[i].render.draw.y < y
				|| t->hit.u_ptr.h[i].render.pdist > t->zbuffer[x - t->dx][y])
				continue ;
			if (t->hit.u_ptr.h[i].render.hit == 2)
				ft_drawdoorpixel(t, x, y, &t->hit.u_ptr.h[i].render);
			else if (t->hit.u_ptr.h[i].render.hit == 3)
				ft_drawtpixel(t, x, y, &t->hit.u_ptr.h[i].render);
			else if (t->hit.u_ptr.h[i].render.hit > 3
				&& t->hit.u_ptr.h[i].render.hit < 8)
				ft_drawppixel(t, x, y, &t->hit.u_ptr.h[i].render);
			else if (t->hit.u_ptr.h[i].render.hit == 8)
				ft_drawspixel(t, x, y, &t->hit.u_ptr.h[i].render);
		}
	}
}

void	ft_drawhit(t_thread *t, t_render *r)
{
	ft_drawsprites(t);
	r->pass = true;
	r->p.x = t->dx;
	while (r->p.x < t->x)
	{
		ft_rays(t->g, r, r->p.x, t);
		ft_drawhitrow(t, r->p.x);
		r->p.x += 2;
	}
}
