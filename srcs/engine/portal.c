/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:29:14 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/23 16:00:52 by wouhliss         ###   ########.fr       */
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

static inline int	get_ptex_x(t_render *r, const double wallx, const int tw)
{
	int	val;

	(void)r;
	val = (wallx * tw);
	if (r->side == 1 || r->side == -2)
		val = tw - val - 1;
	return (val);
}

void	ft_portal(const t_game *game, t_render *r)
{
	double	wallx;

	r->pid = r->hit - 4;
	r->ptwidth = game->pt[r->pid].width;
	r->ps = game->pt[r->pid].s;
	wallx = get_wall_x(r);
	r->ptex.x = get_ptex_x(r, wallx, r->ptwidth);
	r->pmystep = (double)r->ptwidth / r->lh;
	r->ptexpos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->pmystep;
	ft_wall(game, r);
}

static inline void	ft_putppixel(t_thread *t, const int x, const int y,
		t_render *r)
{
	t_ui	color;
	t_ui	wcolor;

	color = ((int *)t->g->pt[r->pid].a)[r->ps + r->ptwidth * r->ptex.y
		+ r->ptex.x];
	wcolor = ((int *)t->g->wt[r->id].a)[r->s + r->twidth * r->tex.y + r->tex.x];
	if ((color & 0x00FFFFFF) != 0 && color != 65280)
	{
		t->zbuffer[x - t->dx][y] = r->pdist;
		if (*(((unsigned int *)t->g->s.a) + (y * W) + x) != color)
			*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
	}
	else if (color == 65280)
	{
		t->zbuffer[x - t->dx][y] = r->pdist;
		if (*(((unsigned int *)t->g->s.a) + (y * W) + x) != wcolor)
			*(((unsigned int *)t->g->s.a) + (y * W) + x) = wcolor;
	}
}

void	ft_drawppixel(t_thread *t, const int x, const int y, t_render *r)
{
	unsigned int	color;

	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	r->ptex.y = (int)r->ptexpos & (r->ptwidth - 1);
	r->ptexpos += r->pmystep;
	if (t->g->p.looking && t->g->p.look_pos.x == r->map.x
		&& t->g->p.look_pos.y == r->map.y && (!r->ptex.y
			|| r->ptex.y == r->ptwidth - 1 || !r->ptex.x
			|| r->ptex.x == r->ptwidth - 1))
	{
		color = 0x00FF0000;
		*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
		return ;
	}
	ft_putppixel(t, x, y, r);
}
