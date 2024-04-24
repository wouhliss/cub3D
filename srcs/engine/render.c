/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:55:43 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*ft_hit(const t_game *g, t_render *r, t_thread *t)
{
	t_hit	hit;
	size_t	i;

	if (ic("sgoanmcgvAGlVOrMRtwj", g->m.m[r->m.y][r->m.x]))
	{
		hit.render = *r;
		hit.render.hit = 3;
		if (g->m.m[r->m.y][r->m.x] == 's')
			hit.render.hit = 8;
		return (ft_add_to_vector(g, &t->hit, &hit));
	}
	i = 0;
	while (i < g->doors.index)
	{
		if (!g->doors.u_ptr.d[i].delete && g->doors.u_ptr.d[i].pos.x == r->m.x
			&& g->doors.u_ptr.d[i].pos.y == r->m.y)
		{
			hit.render = *r;
			hit.render.hit = 2;
			hit.render.shift = fabs(g->doors.u_ptr.d[i].frame);
			return (ft_add_to_vector(g, &t->hit, &hit));
		}
		++i;
	}
	return (NULL);
}

void	ft_steps(const t_game *g, t_render *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->sd.x = (g->p.pos.x - r->m.x) * r->dd.x;
	}
	else
	{
		r->step.x = 1;
		r->sd.x = (r->m.x + 1.0 - g->p.pos.x) * r->dd.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->sd.y = (g->p.pos.y - r->m.y) * r->dd.y;
	}
	else
	{
		r->step.y = 1;
		r->sd.y = (r->m.y + 1.0 - g->p.pos.y) * r->dd.y;
	}
}

void	ft_dda(const t_game *g, t_render *r, t_thread *t)
{
	while (!r->hit && t->hit.index < 150)
	{
		if (r->sd.x < r->sd.y)
		{
			r->sd.x += r->dd.x;
			r->m.x += r->step.x;
			r->side = -1;
			r->side -= 1 * (r->step.x < 0);
		}
		else
		{
			r->sd.y += r->dd.y;
			r->m.y += r->step.y;
			r->side = 1;
			r->side += 1 * (r->step.y < 0);
		}
		ft_portal_hit(t, g, r);
		r->c = g->m.m[r->m.y][r->m.x];
		if (r->c == '1')
			r->hit = 1;
		else if (r->c != '0')
			ft_hit(g, r, t);
	}
}

void	ft_rays(const t_game *g, t_render *r, const int x, t_thread *t)
{
	size_t	i;

	r->side = 0;
	t->hit.index = 0;
	r->camera_x = 2.0 * x / ((double)W) - 1.0;
	r->pos = g->p.pos;
	r->ray_dir = (t_vec){(-g->p.dir.x + -g->p.p.x * r->camera_x), g->p.dir.y
		+ g->p.p.y * r->camera_x};
	r->m = (t_intvec){(int)g->p.pos.x, (int)g->p.pos.y};
	r->dd = (t_vec){1e30, 1e30};
	if (r->ray_dir.x)
		r->dd.x = fabs(1.0f / r->ray_dir.x);
	if (r->ray_dir.y)
		r->dd.y = fabs(1.0f / r->ray_dir.y);
	r->hit = 0;
	ft_steps(g, r);
	ft_dda(g, r, t);
	ft_hitcalc(g, r, 0);
	i = 0;
	while (i < t->hit.index)
	{
		ft_hitcalc(g, &t->hit.u_ptr.h[i].render, t->hit.u_ptr.h[i].render.hit);
		++i;
	}
}

void	*ft_draw(void *p)
{
	t_render	r;
	t_thread	*t;

	t = p;
	r.p.x = t->dx;
	while (r.p.x < t->x)
	{
		ft_rays(t->g, &r, r.p.x, t);
		r.p.y = -1;
		while (++r.p.y < HEIGHT)
		{
			t->zbuffer[r.p.x - t->dx][r.p.y] = r.pdist;
			t->tdbuffer[r.p.x - t->dx][r.p.y] = -1;
			if (r.p.y < r.draw.x)
				*(((t_ui *)t->g->s.a) + (r.p.y * W) + r.p.x) = t->g->m.cc.hex;
			else if (r.p.y > r.draw.y)
				*(((t_ui *)t->g->s.a) + (r.p.y * W) + r.p.x) = t->g->m.fc.hex;
			else
				ft_drawwallpixel(t->g, r.p.x, r.p.y, &r);
		}
		ft_drawhitrow(t, r.p.x);
		r.p.x += 2;
	}
	ft_drawsprites(t);
	return (NULL);
}
