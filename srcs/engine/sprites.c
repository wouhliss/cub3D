/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:15:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/28 11:51:22 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline t_intvec	ft_gety(t_game *game, t_sprite *s, t_render *render)
{
	t_intvec	draw_y;

	render->sph = abs((int)(HEIGHT / (render->transform.y))) / s->vr;
	draw_y.x = -render->sph / 2 + HALF_HEIGHT + game->p.y + s->vpos;
	if (draw_y.x < 0)
		draw_y.x = 0;
	draw_y.y = render->sph / 2 + HALF_HEIGHT + game->p.y + s->vpos;
	if (draw_y.y >= HEIGHT)
		draw_y.y = HEIGHT - 1;
	return (draw_y);
}

static inline t_intvec	ft_getx(t_sprite *s, t_render *render, int w)
{
	t_intvec	draw_x;

	render->spritewidth = abs((int)(HEIGHT / (render->transform.y))) / s->hr;
	draw_x.x = -render->spritewidth / 2 + render->spsx;
	if (draw_x.x < 0)
		draw_x.x = 0;
	draw_x.y = render->spritewidth / 2 + render->spsx;
	if (draw_x.y >= w)
		draw_x.y = w - 1;
	return (draw_x);
}

static inline void	ft_putsprite(t_game *g, t_sprite *s, t_screen *screen, t_render *render, int dx)
{
	t_intvec	d;
	t_intvec	tex;
	int			color;

	d.x = render->draw_x.x - 1;
	while (++d.x < render->draw_x.y)
	{
		tex.x = (int)(256 * (d.x - (-render->spritewidth / 2 + render->spsx))
				* s->t->width / render->spritewidth) / 256;
		if (render->transform.y > 0 && d.x > 0 && d.x < WIDTH
			&& render->transform.y < render->zbuffer[d.x])
		{
			d.y = render->draw_y.x - 1;
			while (++d.y < render->draw_y.y)
			{
				tex.y = ((((d.y - g->p.y - s->vpos) * 256 - HEIGHT * 128
								+ render->sph * 128) * s->t->width) / render->sph)
					/ 256;
				color = 0;
				if (tex.y > 0)
					color = ((int *)s->t->addr)[s->t->s + s->t->width * tex.y
						+ tex.x];
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(screen, d.x - dx, d.y, color);
			}
		}
	}
}

static inline void	ft_sort_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->numsprites)
	{
		game->sprite_order[i] = i;
		game->sprite_dist[i] = ((game->p.pos.x - game->sprites[i].pos.x)
				* (game->p.pos.x - game->sprites[i].pos.x) + (game->p.pos.y
					- game->sprites[i].pos.y) * (game->p.pos.y
					- game->sprites[i].pos.y));
		++i;
	}
	i = 0;
	while (i + 1 < game->numsprites)
	{
		if (game->sprite_dist[i] < game->sprite_dist[i + 1])
		{
			ft_swapi(&game->sprite_order[i], &game->sprite_order[i + 1]);
			ft_swapd(&game->sprite_dist[i], &game->sprite_dist[i + 1]);
			i = 0;
		}
		else
			++i;
	}
}

inline void	ft_drawsprites(t_game *game, t_screen *screen, int dx, t_render *render, int w)
{
	int			i;
	t_sprite	*s;

	ft_sort_sprites(game);
	i = 0;
	while (i < game->numsprites)
	{
		s = &game->sprites[game->sprite_order[i]];
		render->sprite.x = s->pos.x - game->p.pos.x;
		render->sprite.y = s->pos.y - game->p.pos.y;
		render->invdet = 1.0 / (game->p.plane.x * game->p.dir.y - game->p.dir.x
				* game->p.plane.y);
		render->transform.x = render->invdet * (game->p.dir.y * render->sprite.x
				- game->p.dir.x * render->sprite.y);
		render->transform.y = render->invdet * (-game->p.plane.y
				* render->sprite.x + game->p.plane.x * render->sprite.y);
		render->spsx = (int)((HALF_WIDTH) * (1.0 + render->transform.x
					/ render->transform.y));
		s->vpos = (int)(s->vdiff / render->transform.y);
		render->draw_x = ft_getx(s, render, w);
		render->draw_y = ft_gety(game, s, render);
		ft_putsprite(game, s, screen, render, dx);
		++i;
	}
}
