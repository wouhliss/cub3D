/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:38:23 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 17:34:00 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline t_intvec	ft_gety(t_game *game, const t_sprite *s, t_render *r)
{
	t_intvec	draw_y;

	r->sph = abs((int)(HEIGHT / (r->t.y))) / s->vr;
	draw_y.x = -r->sph / 2 + HALF_HEIGHT + game->p.y + ((int)(game->p.jump)
			/ r->t.y) + r->vpos;
	if (draw_y.x < 0)
		draw_y.x = 0;
	draw_y.y = r->sph / 2 + HALF_HEIGHT + game->p.y + ((int)(game->p.jump)
			/ r->t.y) + r->vpos;
	if (draw_y.y >= HEIGHT)
		draw_y.y = HEIGHT - 1;
	return (draw_y);
}

static inline t_intvec	ft_getx(t_render *r, const t_sprite *s, const int x,
		const int dx)
{
	t_intvec	draw_x;

	r->spritewidth = abs((int)(HEIGHT / (r->t.y))) / s->hr;
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
	t_intvec	tex;
	t_intvec	d;
	int			color;

	d.x = r->draw_x.x - 1;
	while (++d.x < r->draw_x.y)
	{
		tex.x = (int)(256 * (d.x - (-r->spritewidth / 2 + r->spsx))
				* g->st[s->type].width / r->spritewidth) / 256;
		if (r->t.y > 0 && d.x > 0 && d.x < W)
		{
			d.y = r->draw_y.x - 1;
			while (++d.y < r->draw_y.y)
			{
				tex.y = ((((d.y - g->p.y - ((int)(g->p.jump) / r->t.y)
									- r->vpos) * 256 - HEIGHT * 128 + r->sph
								* 128) * g->st[s->type].width) / r->sph) / 256;
				color = 0;
				if (tex.y > 0 && tex.y < g->st[s->type].width)
					color = ((int *)g->st[s->type].a)[g->st[s->type].s
						+ g->st[s->type].width * tex.y + tex.x];
				if ((color & 0x00FFFFFF) != 0 && r->t.y < t->zbuffer[d.x
					- t->dx][d.y])
				{
					*(((t_ui *)t->g->s.a) + (d.y * W) + d.x) = color;
					if (t->tdbuffer[d.x - t->dx][d.y] > 0 && r->t.y > t->tdbuffer[d.x - t->dx][d.y])
						my_mlx_pixel_tput(&g->s, d.x, d.y, t->tbuffer[d.x - t->dx][d.y]);
					t->zbuffer[d.x - t->dx][d.y] = r->t.y;
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
		if (t->g->sprites.u_ptr.s[i].hide)
		{
			++i;
			continue ;
		}
		r.sp.x = t->g->sprites.u_ptr.s[i].pos.x - t->g->p.pos.x;
		r.sp.y = t->g->sprites.u_ptr.s[i].pos.y - t->g->p.pos.y;
		r.ind = 1.0 / (t->g->p.p.x * t->g->p.dir.y - t->g->p.dir.x
				* t->g->p.p.y);
		r.t.x = r.ind * (t->g->p.dir.y * -r.sp.x - t->g->p.dir.x * r.sp.y);
		r.t.y = r.ind * (-t->g->p.p.y * -r.sp.x + t->g->p.p.x * r.sp.y);
		r.spsx = (int)((HW) * (1.0 + r.t.x / r.t.y));
		r.vpos = (int)(t->g->sprites.u_ptr.s[i].vdiff / r.t.y);
		r.draw_x = ft_getx(&r, &t->g->sprites.u_ptr.s[i], t->x, t->dx);
		r.draw_y = ft_gety(t->g, &t->g->sprites.u_ptr.s[i], &r);
		ft_putsprite(t->g, &t->g->sprites.u_ptr.s[i], &r, t);
		++i;
	}
}
