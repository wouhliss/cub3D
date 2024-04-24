/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:12:43 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:51 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_delete_projectile(t_game *g, const int i,
		const double step)
{
	g->map.map[(int)(g->pls.u_ptr.p[i].sprite->pos.y
			+ g->pls.u_ptr.p[i].sprite->dir.y
			* step)][(int)(g->pls.u_ptr.p[i].sprite->pos.x
			+ -g->pls.u_ptr.p[i].sprite->dir.x * step)] = '0';
	g->pls.u_ptr.p[i].delete = 1;
	g->pls.u_ptr.p[i].sprite->delete = 1;
	g->pls.u_ptr.p[i].sprite->hide = 1;
}

static inline void	ft_portal_step(t_game *g, const int i, const double step)
{
	if (g->pls.u_ptr.p[i].type == 0 && ft_oob(g, g->pls.u_ptr.p[i].sprite->pos.x
			+ -g->pls.u_ptr.p[i].sprite->dir.x * step,
			g->pls.u_ptr.p[i].sprite->pos.y + g->pls.u_ptr.p[i].sprite->dir.y
			* step))
	{
		g->pls.u_ptr.p[i].delete = 1;
		g->pls.u_ptr.p[i].sprite->delete = 1;
		g->pls.u_ptr.p[i].sprite->hide = 1;
	}
	else if (g->pls.u_ptr.p[i].type == 1)
	{
		g->pls.u_ptr.p[i].map = (t_intvec){(int)g->pls.u_ptr.p[i].sprite->pos.x,
			(int)g->pls.u_ptr.p[i].sprite->pos.y};
		ft_psteps(&g->pls.u_ptr.p[i]);
		ft_pdda(g, &g->pls.u_ptr.p[i]);
	}
	else if (g->pls.u_ptr.p[i].type == 2)
	{
		g->pls.u_ptr.p[i].map = (t_intvec){(int)g->pls.u_ptr.p[i].sprite->pos.x,
			(int)g->pls.u_ptr.p[i].sprite->pos.y};
		ft_psteps(&g->pls.u_ptr.p[i]);
		ft_pdda(g, &g->pls.u_ptr.p[i]);
	}
}

void	ft_handle_pls(t_game *g)
{
	double	step;
	size_t	i;

	i = 0;
	while (i < g->pls.index)
	{
		step = 0.0;
		while (!g->pls.u_ptr.p[i].sprite->hide && step < g->delta * 0.00000002)
		{
			if (g->pls.u_ptr.p[i].type == 0 && ft_candelete(g,
					g->pls.u_ptr.p[i].sprite->pos.x
					+ -g->pls.u_ptr.p[i].sprite->dir.x * step,
					g->pls.u_ptr.p[i].sprite->pos.y
					+ g->pls.u_ptr.p[i].sprite->dir.y * step))
				ft_delete_projectile(g, i, step);
			ft_portal_step(g, i, step);
			step += 0.001;
		}
		g->pls.u_ptr.p[i].sprite->pos = (t_vec){g->pls.u_ptr.p[i].sprite->pos.x
			+ -g->pls.u_ptr.p[i].sprite->dir.x * g->delta * 0.00000002,
			g->pls.u_ptr.p[i].sprite->pos.y + g->pls.u_ptr.p[i].sprite->dir.y
			* g->delta * 0.00000002};
		++i;
	}
}

void	ft_add_projectile(t_game *g, t_vec pos, t_vec dir, int type)
{
	t_sprite		sprite;
	t_projectile	projectile;

	sprite = (t_sprite){.type = 2, .vdiff = 64.0, .hr = 4, .vr = 4, .hide = 0,
		.pos = pos, .dir = dir};
	projectile = (t_projectile){.type = type, .delete = 0,
		.sprite = ft_add_to_vector(g, &g->sprites, &sprite)};
	ft_add_to_vector(g, &g->pls, &projectile);
}
