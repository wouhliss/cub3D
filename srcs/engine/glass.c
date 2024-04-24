/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:40:51 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 18:07:38 by wouhliss         ###   ########.fr       */
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

static inline int	get_tex_x(t_render *r, const double wallx, const int tw)
{
	int	val;

	(void)r;
	val = (wallx * tw);
	if (r->side == 1 || r->side == -2)
		val = tw - val - 1;
	return (val);
}

void	ft_glass(const t_game *game, t_render *r)
{
	double	wallx;

	switch (r->c)
	{
		case 'n':
			r->id = 1;
			break ;
		case 'a':
			r->id = 2;
			break ;
		case 'm':
			r->id = 3;
			break ;
		case 'c':
			r->id = 4;
			break ;
		case 'g':
			r->id = 5;
			break ;
		case 'v':
			r->id = 6;
			break ;
		case 'A':
			r->id = 7;
			break ;
		case 'l':
			r->id = 8;
			break;
		case 'M':
			r->id = 9;
			break;
		case 'r':
			r->id = 10;
			break;
		case 'V':
			r->id = 11;
			break;
		case 'O':
			r->id = 12;
			break;
		case 'G':
			r->id = 13;
			break;
		case 'w':
			r->id = 14;
			break;
		case 'j':
			r->id = 15;
			break;
		case 't':
			r->id = 16;
			break;
		case 'o':
			r->id = 17;
			break;
		default:
			r->id = 0;
			break;
	}
	r->twidth = game->gt[r->id].width;
	r->s = game->gt[r->id].s;
	wallx = get_wall_x(r);
	r->tex.x = get_tex_x(r, wallx, r->twidth);
	r->linetex.x = get_tex_x(r, wallx, 64);
	r->mystep = (double)r->twidth / r->lh;
	r->linestep = (double)64 / r->lh;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->mystep;
	r->linepos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->linestep;
	r->s = game->gt[r->id].s;
}

void	ft_drawtpixel(t_thread *t, const int x, const int y, t_render *r)
{
	unsigned int	color;

	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	r->linetex.y = (int)r->linepos & (63);
	r->linepos += r->linestep;
	if (t->g->p.looking && t->g->p.look_pos.x == r->map.x
		&& t->g->p.look_pos.y == r->map.y && (!r->linetex.y
			|| r->linetex.y == 63 || !r->linetex.x || r->linetex.x == 63))
	{
		color = 0x00FF0000;
		*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
		t->zbuffer[x - t->dx][y] = r->pdist;
		return ;
	}
	color = ((int *)t->g->gt[r->id].a)[r->s + r->twidth * r->tex.y + r->tex.x];
	if ((color & 0x00FFFFFF) != 0)
	{
		my_mlx_pixel_tput(&t->g->s, x, y, color);
		t->tbuffer[x - t->dx][y] = color;
		t->tdbuffer[x - t->dx][y] = r->pdist;
	}
}
