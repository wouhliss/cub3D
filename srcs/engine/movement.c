/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:00:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/14 11:53:25 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_check_doors(t_game *g, const double x, const double y)
{
	size_t	i;

	i = 0;
	while (i < g->doors.index)
	{
		if (g->doors.ptr.d[i].state != OPEN
			&& g->doors.ptr.d[i].pos.x >= (int)((g->p.pos.x + x) - 0.1)
			&& g->doors.ptr.d[i].pos.x <= (int)((g->p.pos.x + x) + 0.1)
			&& g->doors.ptr.d[i].pos.y >= (int)((g->p.pos.y + y) - 0.1)
			&& g->doors.ptr.d[i].pos.y <= (int)((g->p.pos.y + y) + 0.1))
			return (true);
		++i;
	}
	return (false);
}

bool	ft_can_move(t_game *g, const double x, const double y)
{
	if ((g->p.pos.x + x) <= 1.1 || (g->p.pos.x + x) >= g->width - 1.1
		|| (g->p.pos.y + y) <= 1.1 || (g->p.pos.y + y) >= g->length - 1.1)
		return (false);
	if (x < 0.0 && g->map.map[(int)(g->p.pos.y + y)][(int)((g->p.pos.x + x)
			- 0.1)] == '1')
		return (false);
	if (x > 0.0 && g->map.map[(int)(g->p.pos.y + y)][(int)((g->p.pos.x + x)
			+ 0.1)] == '1')
		return (false);
	if (y < 0.0 && g->map.map[(int)((g->p.pos.y + y) - 0.1)][(int)(g->p.pos.x
			+ x)] == '1')
		return (false);
	if (y > 0.0 && g->map.map[(int)((g->p.pos.y + y) + 0.1)][(int)(g->p.pos.x
			+ x)] == '1')
		return (false);
	if (ft_check_doors(g, x, y))
		return (false);
	return (true);
}

static inline void	ft_move_x(t_game *g, int ms)
{
	double	speed;

	if (g->p.jumping == FALLING)
		g->p.jump -= 1.8 * ms;
	if (g->p.jump <= 0.0)
	{
		g->p.jump = 0.0;
		g->p.jumping = GROUND;
	}
	speed = g->p.speed.x;
	while (speed && ms > 0 && ft_can_move(g, speed * 0.01, 0))
	{
		g->p.pos.x += speed * 0.01;
		speed *= 0.99;
		--ms;
	}
}

static inline void	ft_move_y(t_game *g, int ms)
{
	double	speed;

	speed = g->p.speed.y;
	while (speed && ms > 0 && ft_can_move(g, 0, speed * 0.01))
	{
		g->p.pos.y += speed * 0.01;
		speed *= 0.99;
		--ms;
	}
}

static inline void	ft_move_player(t_game *g, const double speed,
		const double sangle)
{
	float	ms;

	if (g->right && !g->left)
	{
		g->p.speed.x += speed * 0.4 * cos(sangle);
		g->p.speed.y += speed * 0.4 * sin(sangle);
	}
	ms = g->delta / 1000000.0;
	if (ms < 1.0)
		ms = 1.0;
	if (ms > 50.0)
		ms = 50.0;
	if (g->space && g->p.jumping == GROUND)
		g->p.jumping = JUMPING;
	if (g->p.jumping == JUMPING)
		g->p.jump += 1.5 * ms;
	if (g->p.jump >= 300.0)
	{
		g->p.jump = 300.0;
		g->p.jumping = FALLING;
	}
	ft_move_x(g, ms);
	g->p.speed.x *= 1.0 - ms / 50.0;
	ft_move_y(g, ms);
	g->p.speed.y *= 1.0 - ms / 50.0;
}

void	ft_handle_movement(t_game *g)
{
	double	speed;
	double	angle;
	double	sangle;

	speed = g->delta / 60000000.0;
	speed += g->shift * 0.6 * speed;
	angle = atan2(g->p.dir.y, -g->p.dir.x);
	sangle = atan2(-g->p.dir.x, -g->p.dir.y);
	if (g->front && !g->back)
	{
		g->p.speed.x += speed * cos(angle);
		g->p.speed.y += speed * sin(angle);
	}
	if (g->back && !g->front)
	{
		g->p.speed.x -= speed * 0.4 * cos(angle);
		g->p.speed.y -= speed * 0.4 * sin(angle);
	}
	if (g->left && !g->right)
	{
		g->p.speed.x -= speed * 0.4 * cos(sangle);
		g->p.speed.y -= speed * 0.4 * sin(sangle);
	}
	ft_move_player(g, speed, sangle);
}
