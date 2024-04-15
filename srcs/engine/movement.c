/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:00:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/15 21:36:04 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_move_x(t_game *g, int ms)
{
	double	speed;

	if (g->p.jumping == FALLING)
		g->p.jump -= HEIGHT / 300 * ms;
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
	if (!ft_can_move(g, speed * 0.01, 0))
		g->p.pos.x -= speed * 0.01;
	else if (!ft_can_move(g, -speed * 0.01, 0))
		g->p.pos.x += speed * 0.01;
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
	if (!ft_can_move(g, 0, speed * 0.01))
		g->p.pos.y -= speed * 0.01;
	else if (!ft_can_move(g, 0, -speed * 0.01))
		g->p.pos.y += speed * 0.01;
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
		g->p.jump += HEIGHT / 350 * ms;
	if (g->p.jump >= HEIGHT / 2)
	{
		g->p.jump = HEIGHT / 2;
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
