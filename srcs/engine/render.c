/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/13 14:59:57 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_hit(const t_game *g, const t_render *r, t_thread *t)
{
	t_hit	hit;
	size_t	i;

	i = 0;
	while (i < g->doors.index)
	{
		if (g->doors.ptr.d[i].pos.x == r->map.x
			&& g->doors.ptr.d[i].pos.y == r->map.y)
		{
			hit.render = *r;
			hit.render.hit = 2;
			hit.render.shift = fabs(g->doors.ptr.d[i].frame);
			ft_add_to_vector(&t->hit, &hit);
		}
		++i;
	}
}

static inline void	ft_steps(const t_game *g, t_render *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (g->p.pos.x - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1.0 - g->p.pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (g->p.pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0 - g->p.pos.y) * r->delta_dist.y;
	}
}

static inline void	ft_dda(const t_game *g, t_render *r, t_thread *t)
{
	t->hit.index = 0;
	while (!r->hit && !ft_outside(g, r->map.x, r->map.y))
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = -1;
			if (r->step.x < 0)
				r->side = -2;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
			if (r->step.y < 0)
				r->side = 2;
		}
		if (!ft_outside(g, r->map.x, r->map.y)
			&& g->map.map[r->map.y][r->map.x] == '1')
			r->hit = 1;
		ft_hit(g, r, t);
	}
}

static inline void	ft_rays(const t_game *g, t_render *r, const int x,
		t_thread *t)
{
	size_t	i;

	r->camera_x = 2.0 * x / ((double)W) - 1.0;
	r->pos = g->p.pos;
	r->ray_dir = (t_vec){-(g->p.dir.x + g->p.p.x * r->camera_x), g->p.dir.y
		+ g->p.p.y * r->camera_x};
	r->map = (t_intvec){(int)g->p.pos.x, (int)g->p.pos.y};
	r->delta_dist = (t_vec){1e30, 1e30};
	if (r->ray_dir.x)
		r->delta_dist.x = fabs(1.0f / r->ray_dir.x);
	if (r->ray_dir.y)
		r->delta_dist.y = fabs(1.0f / r->ray_dir.y);
	r->hit = 0;
	ft_steps(g, r);
	ft_dda(g, r, t);
	ft_hitcalc(g, r, 0);
	i = 0;
	while (i < t->hit.index)
	{
		ft_hitcalc(g, &t->hit.ptr.h[i].render, 1);
		++i;
	}
}

void	*ft_draw(void *p)
{
	t_render	r;
	t_thread	*t;

	t = p;
	r.side = 0;
	t->dx = T_WIDTH * t->id;
	t->x = T_WIDTH * (t->id + 1);
	r.p.x = t->dx - 1;
	while (++r.p.x < T_WIDTH * (t->id + 1))
	{
		ft_rays(t->g, &r, r.p.x, t);
		r.p.y = -1;
		while (++r.p.y < HEIGHT)
		{
			t->zbuffer[r.p.x - t->dx][r.p.y] = r.pdist;
			if (r.p.y < r.draw.x)
				*(((t_ui *)t->g->s.a) + (r.p.y * W) + r.p.x) = t->g->map.cc.hex;
			else if (r.p.y > r.draw.y)
				*(((t_ui *)t->g->s.a) + (r.p.y * W) + r.p.x) = t->g->map.fc.hex;
			else
				ft_drawwallpixel(t->g, r.p.x, r.p.y, &r);
		}
		ft_drawhit(t, r.p.x);
	}
	return (NULL);
}
