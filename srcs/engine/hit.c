/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:43:32 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:19:07 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_calcdraw(const t_game *g, t_render *r, const int t)
{
	if (t == 2)
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

void	ft_hitcalc(const t_game *g, t_render *r, const int t)
{
	ft_calcdraw(g, r, t);
	if (t == 2)
		ft_door(g, r);
	else if (t == 3)
		ft_glass(g, r);
	else if (t > 3 && t < 8)
		ft_portal(g, r);
	else if (t == 8)
		ft_truc(g, r);
	else
		ft_wall(g, r);
}

void	ft_drawhitrow(t_thread *t, const int x)
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
