/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:15:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/27 15:57:05 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline t_intvec	ft_gety(t_game *game, t_sprite *s)
{
	t_intvec	draw_y;

	game->r.sph = abs((int)(HEIGHT / (game->r.transform.y))) / s->vr;
	draw_y.x = -game->r.sph / 2 + HALF_HEIGHT + game->p.y + s->vpos;
	if (draw_y.x < 0)
		draw_y.x = 0;
	draw_y.y = game->r.sph / 2 + HALF_HEIGHT + game->p.y + s->vpos;
	if (draw_y.y >= HEIGHT)
		draw_y.y = HEIGHT - 1;
	return (draw_y);
}

static inline t_intvec	ft_getx(t_game *game, t_sprite *s)
{
	t_intvec	draw_x;

	game->r.spritewidth = abs((int)(HEIGHT / (game->r.transform.y))) / s->hr;
	draw_x.x = -game->r.spritewidth / 2 + game->r.spsx;
	if (draw_x.x < 0)
		draw_x.x = 0;
	draw_x.y = game->r.spritewidth / 2 + game->r.spsx;
	if (draw_x.y >= WIDTH)
		draw_x.y = WIDTH - 1;
	return (draw_x);
}

static inline void	ft_putsprite(t_game *g, t_sprite *s)
{
	t_intvec	d;
	t_intvec	tex;
	int			color;

	d.x = g->r.draw_x.x - 1;
	while (++d.x < g->r.draw_x.y)
	{
		tex.x = (int)(256 * (d.x - (-g->r.spritewidth / 2 + g->r.spsx))
				* s->t->width / g->r.spritewidth) / 256;
		if (g->r.transform.y > 0 && d.x > 0 && d.x < WIDTH
			&& g->r.transform.y < g->r.zbuffer[d.x])
		{
			d.y = g->r.draw_y.x - 1;
			while (++d.y < g->r.draw_y.y)
			{
				tex.y = ((((d.y - g->p.y - s->vpos) * 256 - HEIGHT * 128
								+ g->r.sph * 128) * s->t->width) / g->r.sph)
					/ 256;
				color = 0;
				if (tex.y > 0)
					color = ((int *)s->t->addr)[s->t->width * tex.y + tex.x];
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&g->screen, d.x, d.y, color);
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

inline void	ft_drawsprites(t_game *game)
{
	int			i;
	t_sprite	*s;

	ft_sort_sprites(game);
	i = 0;
	while (i < game->numsprites)
	{
		s = &game->sprites[game->sprite_order[i]];
		game->r.sprite.x = s->pos.x - game->p.pos.x;
		game->r.sprite.y = s->pos.y - game->p.pos.y;
		game->r.invdet = 1.0 / (game->p.plane.x * game->p.dir.y - game->p.dir.x
				* game->p.plane.y);
		game->r.transform.x = game->r.invdet * (game->p.dir.y * game->r.sprite.x
				- game->p.dir.x * game->r.sprite.y);
		game->r.transform.y = game->r.invdet * (-game->p.plane.y
				* game->r.sprite.x + game->p.plane.x * game->r.sprite.y);
		game->r.spsx = (int)((HALF_WIDTH) * (1.0 + game->r.transform.x
					/ game->r.transform.y));
		s->vpos = (int)(s->vdiff / game->r.transform.y);
		game->r.draw_x = ft_getx(game, s);
		game->r.draw_y = ft_gety(game, s);
		ft_putsprite(game, s);
		++i;
	}
}
