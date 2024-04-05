/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:00:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/05 08:36:49 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_can_move(t_game *g, int x, int y)
{
	return (x < g->width && x > 0 && y < g->length && y > 0
		&& g->map.map[y][x] != '1');
}

static inline void	ft_move_player(t_game *g)
{
	if (ft_can_move(g, (int)(g->p.pos.x + g->p.speed.x - g->p.speed.x * 0.85),
			(int)(g->p.pos.y)))
		g->p.pos.x += g->p.speed.x - g->p.speed.x * 0.85;
	g->p.speed.x *= 0.85;
	if (ft_can_move(g, (int)(g->p.pos.x), (int)(g->p.pos.y + g->p.speed.y - g->p.speed.y * 0.85)))
		g->p.pos.y += g->p.speed.y - g->p.speed.y * 0.85;
	g->p.speed.y *= 0.85;
}

void	ft_handle_movement(t_game *g)
{
	float	speed;

	speed = g->delta * 0.000000003f;
	speed += speed * 0.5 * g->shift;
	if (g->front && !g->back)
	{
		g->p.speed.x += speed * -g->p.dir.x;
		g->p.speed.y += speed * g->p.dir.y;
	}
	if (g->back && !g->front)
	{
		g->p.speed.x -= speed / 2 * -g->p.dir.x;
		g->p.speed.y -= speed / 2 * g->p.dir.y;
	}
	if (g->left)
	{
		g->p.speed.x -= speed / 2 * (-g->p.dir.x * cos((HALF_PI)) - g->p.dir.y
			* sin((HALF_PI)));
		g->p.speed.y -= speed / 2 * (-g->p.dir.x * sin((HALF_PI)) + g->p.dir.y
			* cos((HALF_PI)));
	}
	if (g->right)
	{
		g->p.speed.x += speed / 2 * (-g->p.dir.x * cos((HALF_PI)) - g->p.dir.y
			* sin((HALF_PI)));
		g->p.speed.y += speed / 2 * (-g->p.dir.x * sin((HALF_PI)) + g->p.dir.y
			* cos((HALF_PI)));
	}
	ft_move_player(g);
}
