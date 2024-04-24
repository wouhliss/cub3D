/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:11:20 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:55:43 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_candelete(t_game *game, double x, double y)
{
	return (x >= 1.0 && y >= 1.0 && (int)x < game->w - 1
		&& (int)y < game->length - 1);
}

bool	ft_oob(t_game *game, double x, double y)
{
	return (x <= 1.0 || y <= 1.0 || (int)x >= game->w
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
		p->sd.x = (p->sprite->pos.x - p->m.x) * p->dd.x;
	}
	else
	{
		p->step.x = 1;
		p->sd.x = (p->m.x + 1.0 - p->sprite->pos.x) * p->dd.x;
	}
	if (p->sprite->dir.y < 0)
	{
		p->step.y = -1;
		p->sd.y = (p->sprite->pos.y - p->m.y) * p->dd.y;
	}
	else
	{
		p->step.y = 1;
		p->sd.y = (p->m.y + 1.0 - p->sprite->pos.y) * p->dd.y;
	}
}

static inline void	ft_hitdda(t_game *g, t_projectile *p)
{
	if (!ft_outside(g, p->m.x, p->m.y)
		&& g->m.m[p->m.y][p->m.x] == '1')
	{
		p->sprite->hide = 1;
		if (p->t == 1)
		{
			g->pl.pos = p->m;
			g->pl.side = p->side;
			if (g->pr.pos.x == g->pl.pos.x
				&& g->pr.pos.y == g->pl.pos.y
				&& g->pr.side == g->pl.side)
				g->pr.side = 0;
		}
		else if (p->t == 2)
		{
			g->pr.pos = p->m;
			g->pr.side = p->side;
			if (g->pr.pos.x == g->pl.pos.x
				&& g->pr.pos.y == g->pl.pos.y
				&& g->pr.side == g->pl.side)
				g->pl.side = 0;
		}
	}
	else if (ft_projectile_hit(g, p))
		return ;
}

void	ft_pdda(t_game *game, t_projectile *p)
{
	while (!p->sprite->hide && !ft_outside(game, p->m.x, p->m.y))
	{
		if (p->sd.x < p->sd.y)
		{
			p->sd.x += p->dd.x;
			p->m.x += p->step.x;
			p->pdist = p->sd.x - p->dd.x;
			p->side = -1;
			if (p->step.x < 0)
				p->side = -2;
		}
		else
		{
			p->sd.y += p->dd.y;
			p->m.y += p->step.y;
			p->pdist = p->sd.y - p->dd.y;
			p->side = 1;
			if (p->step.y < 0)
				p->side = 2;
		}
		if (p->pdist > game->delta * 0.00000002)
			break ;
		ft_hitdda(game, p);
	}
}
