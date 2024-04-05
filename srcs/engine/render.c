/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/05 08:24:20 by wouhliss         ###   ########.fr       */
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
		r->side_dist.x = (r->map.x + 1.0f - g->p.pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (g->p.pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0f - g->p.pos.y) * r->delta_dist.y;
	}
}

static inline void	ft_dda(const t_game *g, t_render *r)
{
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
	}
}

static inline void	ft_rays(const t_game *g, t_render *r, const int x)
{
	r->camera_x = 2.0f * x / ((float)WIDTH) - 1.0f;
	r->pos = g->p.pos;
	r->ray_dir = (t_vec){-(g->p.dir.x + g->p.p.x * r->camera_x), g->p.dir.y
		+ g->p.p.y * r->camera_x};
	r->map = (t_intvec){(int)g->p.pos.x, (int)g->p.pos.y};
	r->delta_dist = (t_vec){1e30f, 1e30f};
	if (r->ray_dir.x)
		r->delta_dist.x = fabsf(1.0f / r->ray_dir.x);
	if (r->ray_dir.y)
		r->delta_dist.y = fabsf(1.0f / r->ray_dir.y);
	r->hit = 0;
	ft_steps(g, r);
	ft_dda(g, r);
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
}

static inline void	ft_drawpixel(t_game *g, const int x, const int y,
		t_render *r)
{
	g->zbuffer[x][y] = -1;
	if (y < r->draw.x)
		*(((unsigned int *)g->screen.addr) + (y * WIDTH)
				+ x) = g->map.c_color.hex;
	else if (y > r->draw.y)
		*(((unsigned int *)g->screen.addr) + (y * WIDTH)
				+ x) = g->map.f_color.hex;
	else
	{
		ft_drawwallpixel(g, x, y, r);
		g->zbuffer[x][y] = r->pdist;
	}
}

void	ft_draw(t_game *game, const int w, const int dx, t_render *r)
{
	r->side = 0;
	r->pixel.x = dx - 1;
	while (++r->pixel.x < w)
	{
		ft_rays(game, r, r->pixel.x);
		ft_wall(game, r);
		r->pixel.y = -1;
		while (++r->pixel.y < HEIGHT)
			ft_drawpixel(game, r->pixel.x, r->pixel.y, r);
	}
}
