/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:15:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 09:39:17 by wouhliss         ###   ########.fr       */
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

static inline t_intvec	ft_getx(t_render *r, const t_sprite *s, const int x,
		const int dx)
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
		const t_render *r)
{
	t_intvec	d;
	t_intvec	tex;
	int			color;

	d.x = r->draw_x.x - 1;
	while (++d.x < r->draw_x.y)
	{
		tex.x = (int)(256 * (d.x - (-r->spritewidth / 2 + r->spsx))
				* s->t->width / r->spritewidth) / 256;
		if (r->transform.y > 0 && d.x > 0 && d.x < WIDTH)
		{
			d.y = r->draw_y.x - 1;
			while (++d.y < r->draw_y.y)
			{
				tex.y = ((((d.y - g->p.y - ((int)(g->p.jump) / r->transform.y) - r->vpos)
								* 256 - HEIGHT * 128 + r->sph * 128)
							* s->t->width) / r->sph) / 256;
				color = 0;
				if (tex.y > 0 && tex.y < s->t->width)
					color = ((int *)s->t->addr)[s->t->s + s->t->width * tex.y
						+ tex.x];
				if ((color & 0x00FFFFFF) != 0
					&& (r->transform.y < g->zbuffer[d.x][d.y] || g->zbuffer[d.x][d.y] < 0))
				{
					my_mlx_pixel_put(&g->screen, d.x, d.y, color);
					if (g->zbuffer[d.x][d.y] < 0 && r->transform.y > fabs(g->zbuffer[d.x][d.y]))
						my_mlx_pixel_tput(&g->screen, d.x, d.y, create_trgb(0, 127, 127, 127));
					g->zbuffer[d.x][d.y] = r->transform.y;
				}
			}
		}
	}
}

void	ft_drawsprites(t_game *game, const int x, const int dx)
{
	t_sprite	*s;
	t_render	r;

	s = game->sprites;
	while (!game->hsprite && s)
	{
		if (s->hide)
		{
			s = s->next;
			continue ;
		}
		r.sprite.x = s->pos.x - game->p.pos.x;
		r.sprite.y = s->pos.y - game->p.pos.y;
		r.invdet = 1.0 / (game->p.p.x * game->p.dir.y - game->p.dir.x
				* game->p.p.y);
		r.transform.x = r.invdet * (game->p.dir.y * -r.sprite.x - game->p.dir.x
				* r.sprite.y);
		r.transform.y = r.invdet * (-game->p.p.y * -r.sprite.x + game->p.p.x
				* r.sprite.y);
		r.spsx = (int)((HALF_WIDTH) * (1.0 + r.transform.x / r.transform.y));
		r.vpos = (int)(s->vdiff / r.transform.y);
		r.draw_x = ft_getx(&r, s, x, dx);
		r.draw_y = ft_gety(game, s, &r);
		ft_putsprite(game, s, &r);
		s = s->next;
	}
}
