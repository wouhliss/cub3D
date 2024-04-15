/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:40:51 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 00:30:42 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline double	get_wall_x(t_render *r)
{
	double	wallx;

	if (r->side < 0)
		wallx = r->pos.y + r->pdist * r->ray_dir.y;
	else
		wallx = r->pos.x + r->pdist * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

static inline int	get_tex_x(t_render *r, const double wallx)
{
	int	val;

	val = (wallx * r->twidth);
	if (r->side < 0 && r->ray_dir.x > 0)
		val = r->twidth - val - 1;
	if (r->side > 1 && r->ray_dir.y > 0)
		val = r->twidth - val - 1;
	return (val);
}

void	ft_glass(const t_game *game, t_render *r)
{
	double	wallx;

	r->id = 5;
	r->twidth = game->wt[r->id].width;
	r->s = game->wt[r->id].s;
	wallx = get_wall_x(r);
	r->tex.x = get_tex_x(r, wallx);
	r->mystep = (double)r->twidth / r->lh;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->mystep;
}

static inline void	my_mlx_pixel_tput(const t_screen *data, const int x,
		const int y, unsigned int color)
{
	char	*dst;
	t_color	tcolor;
	t_color	scolor;
	t_color	dcolor;

	dst = data->a + (y * data->ll + x * (data->bpp / 8));
	scolor.hex = *(unsigned int *)dst;
	tcolor.hex = color;
	dcolor.t = (0.65 * scolor.t) + (0.35 * tcolor.t);
	dcolor.red = (0.65 * scolor.red) + (0.35 * tcolor.red);
	dcolor.green = (0.65 * scolor.green) + (0.35 * tcolor.green);
	dcolor.blue = (0.65 * scolor.blue) + (0.35 * tcolor.blue);
	*(unsigned int *)dst = dcolor.hex;
}

void	ft_drawtpixel(t_thread *t, const int x, const int y, t_render *r)
{
	unsigned int	color;

	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	if (t->g->p.looking && t->g->p.look_pos.x == r->map.x
		&& t->g->p.look_pos.y == r->map.y && (!r->tex.y || r->tex.y == r->twidth
			- 1 || !r->tex.x || r->tex.x == r->twidth - 1))
	{
		color = 0x00FF0000;
		*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
		return ;
	}
	color = ((int *)t->g->wt[r->id].a)[r->s + r->twidth * r->tex.y + r->tex.x];
	my_mlx_pixel_tput(&t->g->s, x, y, color);
}
