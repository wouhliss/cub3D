/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:12:43 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 01:43:48 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline bool	ft_candelete(t_game *game, double x, double y)
{
	return (x >= 1.0 && y >= 1.0 && (int)x < game->width - 1
		&& (int)y < game->length - 1
		&& game->map.map[(int)(y)][(int)(x)] == '1');
}

static inline bool	ft_oob(t_game *game, double x, double y)
{
	return (x <= 1.0 || y <= 1.0 || (int)x >= game->width
		|| (int)y >= game->length);
}

static inline void	ft_steps(t_projectile *p)
{
	p->dd = (t_vec){1e30, 1e30};
	if (-p->sprite->dir.x)
		p->dd.x = fabs(1.0 / -p->sprite->dir.x);
	if (p->sprite->dir.y)
		p->dd.y = fabs(1.0 / p->sprite->dir.y);
	p->map = (t_intvec){(int)p->sprite->pos.x, (int)p->sprite->pos.y};
	if (-p->sprite->dir.x < 0)
	{
		p->step.x = -1;
		p->sd.x = (p->sprite->pos.x - p->map.x) * p->dd.x;
	}
	else
	{
		p->step.x = 1;
		p->sd.x = (p->map.x + 1.0 - p->sprite->pos.x) * p->dd.x;
	}
	if (p->sprite->dir.y < 0)
	{
		p->step.y = -1;
		p->sd.y = (p->sprite->pos.y - p->map.y) * p->dd.y;
	}
	else
	{
		p->step.y = 1;
		p->sd.y = (p->map.y + 1.0 - p->sprite->pos.y) * p->dd.y;
	}
}

static inline void	ft_dda(t_game *game, t_projectile *p)
{
	while (!p->sprite->hide && !ft_outside(game, p->map.x, p->map.y))
	{
		if (p->sd.x < p->sd.y)
		{
			p->sd.x += p->dd.x;
			p->map.x += p->step.x;
			p->pdist = p->sd.x - p->dd.x;
			p->side = -1;
			if (p->step.x < 0)
				p->side = -2;
		}
		else
		{
			p->sd.y += p->dd.y;
			p->map.y += p->step.y;
			p->pdist = p->sd.y - p->dd.y;
			p->side = 1;
			if (p->step.y < 0)
				p->side = 2;
		}
		if (p->pdist > game->delta * 0.00000001)
			break ;
		if (!ft_outside(game, p->map.x, p->map.y)
			&& game->map.map[p->map.y][p->map.x] == '1')
		{
			p->sprite->hide = 1;
			if (p->type == 1)
			{
				game->portal_l.pos = p->map;
				game->portal_l.side = p->side;
				if (game->portal_r.pos.x == game->portal_l.pos.x
					&& game->portal_r.pos.y == game->portal_l.pos.y
					&& game->portal_r.side == game->portal_l.side)
					game->portal_r.side = 0;
			}
			else if (p->type == 2)
			{
				game->portal_r.pos = p->map;
				game->portal_r.side = p->side;
				if (game->portal_r.pos.x == game->portal_l.pos.x
					&& game->portal_r.pos.y == game->portal_l.pos.y
					&& game->portal_r.side == game->portal_l.side)
					game->portal_l.side = 0;
			}
		}
		else if (!ft_outside(game, p->map.x, p->map.y)
			&& game->map.map[p->map.y][p->map.x] != '0')
		{
			p->sprite->hide = 1;
			p->sprite->delete = 1;
			p->delete = 1;
			return ;
		}
	}
}

void	ft_handle_projectiles(t_game *g)
{
	double	step;
	size_t	i;

	i = 0;
	while (i < g->projectiles.index)
	{
		step = 0.0;
		while (!g->projectiles.u_ptr.p[i].sprite->hide && step < g->delta
			* 0.00000001)
		{
			if (g->projectiles.u_ptr.p[i].type == 0 && ft_candelete(g,
					g->projectiles.u_ptr.p[i].sprite->pos.x +
					-g->projectiles.u_ptr.p[i].sprite->dir.x * step,
					g->projectiles.u_ptr.p[i].sprite->pos.y
					+ g->projectiles.u_ptr.p[i].sprite->dir.y * step))
			{
				g->map.map[(int)(g->projectiles.u_ptr.p[i].sprite->pos.y
						+ g->projectiles.u_ptr.p[i].sprite->dir.y
						* step)][(int)(g->projectiles.u_ptr.p[i].sprite->pos.x +
						-g->projectiles.u_ptr.p[i].sprite->dir.x * step)] = '0';
				if ((int)(g->projectiles.u_ptr.p[i].sprite->pos.y
						+ g->projectiles.u_ptr.p[i].sprite->dir.y
						* step) == g->portal_l.pos.y
					&& (int)(g->projectiles.u_ptr.p[i].sprite->pos.x +
						-g->projectiles.u_ptr.p[i].sprite->dir.x
						* step) == g->portal_l.pos.x)
					g->portal_l.side = 0;
				else if ((int)(g->projectiles.u_ptr.p[i].sprite->pos.y
						+ g->projectiles.u_ptr.p[i].sprite->dir.y
						* step) == g->portal_r.pos.y
					&& (int)(g->projectiles.u_ptr.p[i].sprite->pos.x +
						-g->projectiles.u_ptr.p[i].sprite->dir.x
						* step) == g->portal_r.pos.x)
					g->portal_r.side = 0;
				g->projectiles.u_ptr.p[i].delete = 1;
				g->projectiles.u_ptr.p[i].sprite->delete = 1;
				g->projectiles.u_ptr.p[i].sprite->hide = 1;
			}
			else if (g->projectiles.u_ptr.p[i].type == 0 && ft_oob(g,
					g->projectiles.u_ptr.p[i].sprite->pos.x +
					-g->projectiles.u_ptr.p[i].sprite->dir.x * step,
					g->projectiles.u_ptr.p[i].sprite->pos.y
					+ g->projectiles.u_ptr.p[i].sprite->dir.y * step))
			{
				g->projectiles.u_ptr.p[i].delete = 1;
				g->projectiles.u_ptr.p[i].sprite->delete = 1;
				g->projectiles.u_ptr.p[i].sprite->hide = 1;
			}
			else if (g->projectiles.u_ptr.p[i].type == 1)
			{
				ft_steps(&g->projectiles.u_ptr.p[i]);
				ft_dda(g, &g->projectiles.u_ptr.p[i]);
			}
			else if (g->projectiles.u_ptr.p[i].type == 2)
			{
				ft_steps(&g->projectiles.u_ptr.p[i]);
				ft_dda(g, &g->projectiles.u_ptr.p[i]);
			}
			step += 0.001;
		}
		g->projectiles.u_ptr.p[i].sprite->pos = (t_vec){g->projectiles.u_ptr.p[i].sprite->pos.x
			+ -g->projectiles.u_ptr.p[i].sprite->dir.x * g->delta * 0.00000001,
			g->projectiles.u_ptr.p[i].sprite->pos.y
			+ g->projectiles.u_ptr.p[i].sprite->dir.y * g->delta * 0.00000001};
		++i;
	}
}

void	ft_add_projectile(t_game *g, t_vec pos, t_vec dir, int type)
{
	t_sprite		sprite;
	t_projectile	projectile;

	sprite = (t_sprite){.type = 2, .vdiff = 64.0, .hr = 2, .vr = 2, .hide = 0,
		.pos = pos, .dir = dir};
	projectile = (t_projectile){.type = type, .delete = 0,
		.sprite = ft_add_to_vector(g, &g->sprites, &sprite)};
	ft_add_to_vector(g, &g->projectiles, &projectile);
}
