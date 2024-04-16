/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:11:20 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 03:23:54 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_candelete(t_game *game, double x, double y)
{
	return (x >= 1.0 && y >= 1.0 && (int)x < game->width - 1
		&& (int)y < game->length - 1
		&& game->map.map[(int)(y)][(int)(x)] == '1');
}

bool	ft_oob(t_game *game, double x, double y)
{
	return (x <= 1.0 || y <= 1.0 || (int)x >= game->width
		|| (int)y >= game->length);
}

void	ft_psteps(t_projectile *p)
{
	p->dd = (t_vec){1e30, 1e30};
	if (-p->sprite->dir.x)
		p->dd.x = fabs(1.0 / -p->sprite->dir.x);
	if (p->sprite->dir.y)
		p->dd.y = fabs(1.0 / p->sprite->dir.y);
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

static inline void	ft_hitdda(t_game *g, t_projectile *p)
{
	if (!ft_outside(g, p->map.x, p->map.y)
		&& g->map.map[p->map.y][p->map.x] == '1')
	{
		p->sprite->hide = 1;
		if (p->type == 1)
		{
			g->portal_l.pos = p->map;
			g->portal_l.side = p->side;
			if (g->portal_r.pos.x == g->portal_l.pos.x
				&& g->portal_r.pos.y == g->portal_l.pos.y
				&& g->portal_r.side == g->portal_l.side)
				g->portal_r.side = 0;
		}
		else if (p->type == 2)
		{
			g->portal_r.pos = p->map;
			g->portal_r.side = p->side;
			if (g->portal_r.pos.x == g->portal_l.pos.x
				&& g->portal_r.pos.y == g->portal_l.pos.y
				&& g->portal_r.side == g->portal_l.side)
				g->portal_l.side = 0;
		}
	}
	else if (ft_projectile_hit(g, p))
		return ;
}

void	ft_pdda(t_game *game, t_projectile *p)
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
		ft_hitdda(game, p);
	}
}
