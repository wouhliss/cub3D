/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 04:30:49 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 11:59:35 by wouhliss         ###   ########.fr       */
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
	p->delta_dist = (t_vec){1e30, 1e30};
	if (-p->sprite->dir.x)
		p->delta_dist.x = fabs(1.0 / -p->sprite->dir.x);
	if (p->sprite->dir.y)
		p->delta_dist.y = fabs(1.0 / p->sprite->dir.y);
	p->map = (t_intvec){(int)p->sprite->pos.x, (int)p->sprite->pos.y};
	if (-p->sprite->dir.x < 0)
	{
		p->step.x = -1;
		p->side_dist.x = (p->sprite->pos.x - p->map.x) * p->delta_dist.x;
	}
	else
	{
		p->step.x = 1;
		p->side_dist.x = (p->map.x + 1.0 - p->sprite->pos.x) * p->delta_dist.x;
	}
	if (p->sprite->dir.y < 0)
	{
		p->step.y = -1;
		p->side_dist.y = (p->sprite->pos.y - p->map.y) * p->delta_dist.y;
	}
	else
	{
		p->step.y = 1;
		p->side_dist.y = (p->map.y + 1.0 - p->sprite->pos.y) * p->delta_dist.y;
	}
}

static inline void	ft_dda(t_game *game, t_projectile *p)
{
	while (!p->sprite->hide && !ft_outside(game, p->map.x, p->map.y))
	{
		if (p->side_dist.x < p->side_dist.y)
		{
			p->side_dist.x += p->delta_dist.x;
			p->map.x += p->step.x;
			p->perp_dist = p->side_dist.x - p->delta_dist.x;
			p->side = -1;
			if (p->step.x < 0)
				p->side = -2;
		}
		else
		{
			p->side_dist.y += p->delta_dist.y;
			p->map.y += p->step.y;
			p->perp_dist = p->side_dist.y - p->delta_dist.y;
			p->side = 1;
			if (p->step.y < 0)
				p->side = 2;
		}
		if (p->perp_dist > game->delta * 0.00000001)
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
				return ;
			}
	}
}

void	ft_handle_projectiles(t_game *game)
{
	t_projectile	*p;
	double			step;

	p = game->projectiles;
	while (p)
	{
		step = 0.0;
		while (!p->sprite->hide && step < game->delta * 0.00000001)
		{
			if (p->type == 0 && ft_candelete(game, p->sprite->pos.x +
					-p->sprite->dir.x * step, p->sprite->pos.y
					+ p->sprite->dir.y * step))
			{
				game->map.map[(int)(p->sprite->pos.y + p->sprite->dir.y
						* step)][(int)(p->sprite->pos.x + -p->sprite->dir.x
						* step)] = '0';
				if ((int)(p->sprite->pos.y + p->sprite->dir.y
						* step) == game->portal_l.pos.y && (int)(p->sprite->pos.x + -p->sprite->dir.x
						* step) == game->portal_l.pos.x)
						game->portal_l.side = 0;
				else if ((int)(p->sprite->pos.y + p->sprite->dir.y
						* step) == game->portal_r.pos.y && (int)(p->sprite->pos.x + -p->sprite->dir.x
						* step) == game->portal_r.pos.x)
						game->portal_r.side = 0;
				p->delete = 1;
				p->sprite->delete = 1;
				p->sprite->hide = 1;
			}
			else if (p->type == 0 && ft_oob(game, p->sprite->pos.x +
					-p->sprite->dir.x * step, p->sprite->pos.y
					+ p->sprite->dir.y * step))
			{
				p->delete = 1;
				p->sprite->delete = 1;
				p->sprite->hide = 1;
			}
			else if (p->type == 1)
			{
				ft_steps(p);
				ft_dda(game, p);
			}
			else if (p->type == 2)
			{
				ft_steps(p);
				ft_dda(game, p);
			}
			step += 0.001;
		}
		p->sprite->pos = (t_vec){p->sprite->pos.x + -p->sprite->dir.x
			* game->delta * 0.00000001, p->sprite->pos.y + p->sprite->dir.y
			* game->delta * 0.00000001};
		p = p->next;
	}
}
