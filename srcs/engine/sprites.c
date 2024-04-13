/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:38:23 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/13 15:02:18 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline t_intvec	ft_gety(t_game *game, const t_sprite *s, t_render *r)
{
	t_intvec	draw_y;

	r->sph = abs((int)(HEIGHT / (r->transform.y))) / s->vr;
	draw_y.x = -r->sph / 2 + HALF_HEIGHT + game->p.y + ((int)(game->p.jump) / r->transform.y) + r->vpos;
	if (draw_y.x < 0)
		draw_y.x = 0;
	draw_y.y = r->sph / 2 + HALF_HEIGHT + game->p.y + ((int)(game->p.jump) / r->transform.y) + r->vpos;
	if (draw_y.y >= HEIGHT)
		draw_y.y = HEIGHT - 1;
	return (draw_y);
}

static inline t_intvec	ft_getx(t_render *r, const t_sprite *s, const int x, const int dx)
{
	t_intvec	draw_x;

	r->spritewidth = abs((int)(HEIGHT / (r->transform.y))) / s->hr;
	draw_x.x = -r->spritewidth / 2 + r->spsx;
	if (draw_x.x < dx)
		draw_x.x = dx;
	draw_x.y = r->spritewidth / 2 + r->spsx;
	if (draw_x.y > x)
		draw_x.y = x;
	return (draw_x);
}

static inline void	ft_putsprite(t_game *g, const t_sprite *s,
		const t_render *r, t_thread *t)
{
	(void)g;
	(void)s;
	t_intvec	d;
	// t_intvec	tex;
	int			color;

	d.x = r->draw_x.x - 1;
	while (++d.x < r->draw_x.y)
	{
		// tex.x = (int)(256 * (d.x - (-r->spritewidth / 2 + r->spsx))
		// 		* s->t->width / r->spritewidth) / 256;
		if (r->transform.y > 0 && d.x > 0 && d.x < W)
		{
			d.y = r->draw_y.x - 1;
			while (++d.y < r->draw_y.y)
			{
				// tex.y = ((((d.y - g->p.y - ((int)(g->p.jump) / r->transform.y) - r->vpos)
				// 				* 256 - HEIGHT * 128 + r->sph * 128)
				// 			* s->t->width) / r->sph) / 256;
				color = 0x00FF0000;
				// if (tex.y > 0 && tex.y < s->t->width)
				// 	color = ((int *)s->t->a)[s->t->s + s->t->width * tex.y
				// 		+ tex.x];
				if ((color & 0x00FFFFFF) != 0
					&& r->transform.y < t->zbuffer[d.x - t->dx][d.y])
				{
					*(((t_ui *)t->g->s.a) + (d.y * W) + d.x) = color;
					t->zbuffer[d.x - t->dx][d.y] = r->transform.y;
				}
			}
		}
	}
}

void	ft_drawsprites(t_thread *t)
{
		t_render	r;
	size_t		i;

	i = 0;
	while (i < t->g->sprites.index)
	{
		r.sprite.x = t->g->sprites.ptr.s[i].pos.x - t->g->p.pos.x;
		r.sprite.y = t->g->sprites.ptr.s[i].pos.y - t->g->p.pos.y;
		r.invdet = 1.0 / (t->g->p.p.x * t->g->p.dir.y - t->g->p.dir.x
				* t->g->p.p.y);
		r.transform.x = r.invdet * (t->g->p.dir.y * -r.sprite.x - t->g->p.dir.x
				* r.sprite.y);
		r.transform.y = r.invdet * (-t->g->p.p.y * -r.sprite.x + t->g->p.p.x
				* r.sprite.y);
		r.spsx = (int)((HW) * (1.0 + r.transform.x / r.transform.y));
		r.vpos = (int)(t->g->sprites.ptr.s[i].vdiff / r.transform.y);
		r.draw_x = ft_getx(&r, &t->g->sprites.ptr.s[i], t->x, t->dx);
		r.draw_y = ft_gety(t->g, &t->g->sprites.ptr.s[i], &r);
		ft_putsprite(t->g, &t->g->sprites.ptr.s[i], &r, t);
		++i;
	}
}

void	ft_drawpsprites(t_thread *t, t_vec *pos, t_vec *dir)
{
	(void)pos;
	t_render	r;
	size_t		i;

	i = 0;
	while (i < t->g->sprites.index)
	{
		r.sprite.x = t->g->sprites.ptr.s[i].pos.x - t->g->p.pos.x;
		r.sprite.y = t->g->sprites.ptr.s[i].pos.y - t->g->p.pos.y;
		r.invdet = 1.0 / (t->g->p.p.x * dir->y - dir->x
				* t->g->p.p.y);
		r.transform.x = r.invdet * (dir->y * -r.sprite.x - dir->x
				* r.sprite.y);
		r.transform.y = r.invdet * (-t->g->p.p.y * -r.sprite.x + t->g->p.p.x
				* r.sprite.y);
		r.spsx = (int)((HW) * (1.0 + r.transform.x / r.transform.y));
		r.vpos = (int)(t->g->sprites.ptr.s[i].vdiff / r.transform.y);
		r.draw_x = ft_getx(&r, &t->g->sprites.ptr.s[i], t->x, t->dx);
		r.draw_y = ft_gety(t->g, &t->g->sprites.ptr.s[i], &r);
		ft_putsprite(t->g, &t->g->sprites.ptr.s[i], &r, t);
		++i;
	}
}
