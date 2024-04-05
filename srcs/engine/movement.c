/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:00:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/05 11:29:02 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_can_move(t_game *g, double x, double y)
{
	if (g->p.pos.x + x <= 1.1 || g->p.pos.y + y <= 1.1 || g->p.pos.x
		+ x >= g->width || g->p.pos.y + y >= g->length)
		return (false);
	else if (g->map.map[(int)(g->p.pos.y + y)][(int)(g->p.pos.x + x)] == '1')
		return (false);
	else if (g->map.map[(int)(g->p.pos.y + y + 0.1)][(int)(g->p.pos.x
			+ x)] == '1')
		return (false);
	else if (g->map.map[(int)(g->p.pos.y + y - 0.1)][(int)(g->p.pos.x
			+ x)] == '1')
		return (false);
	else if (g->map.map[(int)(g->p.pos.y + y)][(int)(g->p.pos.x + x
			+ 0.1)] == '1')
		return (false);
	else if (g->map.map[(int)(g->p.pos.y + y)][(int)(g->p.pos.x + x
			- 0.1)] == '1')
		return (false);
	return (true);
}

static inline void	ft_move_x(t_game *g)
{
	double	speed;

	speed = g->p.speed.x;
	while (fabs(speed) > 0.01 && ft_can_move(g, speed * 0.1, 0))
	{
		g->p.pos.x += speed * 0.1;
		speed *= 0.9;
	}
}

static inline void	ft_move_y(t_game *g)
{
	double	speed;

	speed = g->p.speed.y;
	while (fabs(speed) > 0.01 && ft_can_move(g, 0, speed * 0.1))
	{
		g->p.pos.y += speed * 0.1;
		speed *= 0.9;
	}
}

static inline void	ft_move_player(t_game *g)
{
	ft_move_x(g);
	g->p.speed.x *= 0.7;
	ft_move_y(g);
	g->p.speed.y *= 0.7;
}

void	ft_handle_movement(t_game *g)
{
	double	speed;

	speed = g->delta * 0.0000000015;
	speed += speed * 0.3 * g->shift;
	if (g->front && !g->back)
	{
		g->p.speed.x += speed * -g->p.dir.x;
		g->p.speed.y += speed * g->p.dir.y;
	}
	if (g->back && !g->front)
	{
		g->p.speed.x -= speed * 0.6 * -g->p.dir.x;
		g->p.speed.y -= speed * 0.6 * g->p.dir.y;
	}
	if (g->left)
	{
		g->p.speed.x -= speed * 0.7 * -g->p.dir.y;
		g->p.speed.y -= speed * 0.7 * -g->p.dir.x;
	}
	if (g->right)
	{
		g->p.speed.x += speed * 0.7 * -g->p.dir.y;
		g->p.speed.y += speed * 0.7 * -g->p.dir.x;
	}
	// printf("%f, %f\n", g->p.speed.x, g->p.speed.y);
	ft_move_player(g);
}
