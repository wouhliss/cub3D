/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/13 11:44:59 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	t_hit	hit;

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
		for (size_t i = 0; i < g->doors.index; ++i)
		{
			if (g->doors.ptr.d[i].pos.x == r->map.x
				&& g->doors.ptr.d[i].pos.y == r->map.y)
			{
				hit.render = *r;
				hit.render.hit = 2;
				hit.render.shift = g->doors.ptr.d[i].frame;
				ft_add_to_vector(&t->hit, &hit);
			}
		}
		// for (size_t i = 0; i < g->sprites.index; ++i)
		// {
		// 	if (r->map.x == (int)g->sprites.ptr.s[i].pos.x
		// 		&& r->map.y == (int)g->sprites.ptr.s[i].pos.y)
		// 	{
		// 		hit.render = *r;
		// 		hit.render.hit = 3;
		// 		ft_add_to_vector(&t->hit, &hit);
		// 	}
		// }
	}
}

static inline void	ft_rays(const t_game *g, t_render *r, const int x,
		t_thread *t)
{
	r->camera_x = 2.0 * x / ((double)WIDTH) - 1.0;
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
	for (size_t i = 0; i < t->hit.index; ++i)
	{
		if (t->hit.ptr.h[i].render.side > 0)
			t->hit.ptr.h[i].render.pdist = t->hit.ptr.h[i].render.side_dist.y
				- t->hit.ptr.h[i].render.delta_dist.y / 2;
		else
			t->hit.ptr.h[i].render.pdist = t->hit.ptr.h[i].render.side_dist.x
				- t->hit.ptr.h[i].render.delta_dist.x / 2;
		t->hit.ptr.h[i].render.lh = (int)(HEIGHT
				/ t->hit.ptr.h[i].render.pdist);
		t->hit.ptr.h[i].render.draw.x = -t->hit.ptr.h[i].render.lh / 2
			+ HALF_HEIGHT + g->p.y + (int)(g->p.jump)
			/ t->hit.ptr.h[i].render.pdist;
		if (t->hit.ptr.h[i].render.draw.x < 0)
			t->hit.ptr.h[i].render.draw.x = 0;
		t->hit.ptr.h[i].render.draw.y = t->hit.ptr.h[i].render.lh / 2
			+ HALF_HEIGHT + g->p.y + (int)(g->p.jump)
			/ t->hit.ptr.h[i].render.pdist;
		if (t->hit.ptr.h[i].render.draw.y >= HEIGHT)
			t->hit.ptr.h[i].render.draw.y = HEIGHT - 1;
	}
}

static inline void	my_mlx_pixel_tput(const t_screen *data, const int x,
		const int y, unsigned int color)
{
	char	*dst;
	t_color	tcolor;
	t_color	scolor;
	t_color	dcolor;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	scolor.hex = *(unsigned int *)dst;
	tcolor.hex = color;
	dcolor.t = (0.75 * scolor.t) + (0.25 * tcolor.t);
	dcolor.red = (0.75 * scolor.red) + (0.25 * tcolor.red);
	dcolor.green = (0.75 * scolor.green) + (0.25 * tcolor.green);
	dcolor.blue = (0.75 * scolor.blue) + (0.25 * tcolor.blue);
	*(unsigned int *)dst = dcolor.hex;
}

static inline void	ft_drawpixel(t_game *g, const int x, const int y,
		t_render *r, t_thread *t)
{
	g->zbuffer[x][y] = r->pdist;
	if (y < r->draw.x)
		*(((unsigned int *)g->screen.addr) + (y * WIDTH)
				+ x) = g->map.c_color.hex;
	else if (y > r->draw.y)
		*(((unsigned int *)g->screen.addr) + (y * WIDTH)
				+ x) = g->map.f_color.hex;
	else
		ft_drawwallpixel(g, x, y, r);
	for (size_t i = 0; i < t->hit.index; ++i)
	{
		if (y >= t->hit.ptr.h[i].render.draw.x
			&& y <= t->hit.ptr.h[i].render.draw.y
			&& t->hit.ptr.h[i].render.pdist < g->zbuffer[x][y])
			ft_drawwallpixel(g, x, y, &t->hit.ptr.h[i].render);
	}
}

void	*ft_draw(void *p)
{
	t_render	r;
	t_thread	*t;
	int			d;

	t = p;
	d = T_WIDTH * (t->id + 1);
	r.side = 0;
	r.pixel.x = T_WIDTH * t->id - 1;
	while (++r.pixel.x < d)
	{
		t->hit.index = 0;
		ft_rays(t->game, &r, r.pixel.x, t);
		ft_wall(t->game, &r);
		for (size_t i = 0; i < t->hit.index; ++i)
		{
			ft_wall(t->game, &t->hit.ptr.h[i].render);
		}
		r.pixel.y = -1;
		while (++r.pixel.y < HEIGHT)
			ft_drawpixel(t->game, r.pixel.x, r.pixel.y, &r, t);
	}
	return (NULL);
}
