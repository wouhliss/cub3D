/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/05 11:27:11 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_changestate(t_weapon *w)
{
	const int	states[4] = {0, 0, 1, 2};

	if (w->state < states[w->type])
		++w->state;
	else
		w->state = 0;
}

int	on_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;

	(void)x;
	(void)y;
	(void)button;
	game = param;
	(void)game;
	return (0);
}

int	on_mouse_move(int w, int h, void *param)
{
	t_game	*g;
	double	x;
	double	y;

	if (w == HW && h == HALF_HEIGHT)
		return (0);
	g = param;
	x = g->p.dir.x;
	y = g->p.dir.y;
	g->p.dir.x = x * cos((HW - w) * 0.0015) - y * sin((HW - w) * 0.0015);
	g->p.dir.y = x * sin((HW - w) * 0.0015) + y * cos((HW - w) * 0.0015);
	x = g->p.p.x;
	y = g->p.p.y;
	g->p.p.x = x * cos((HW - w) * 0.0015) - y * sin((HW - w) * 0.0015);
	g->p.p.y = x * sin((HW - w) * 0.0015) + y * cos((HW - w) * 0.0015);
	if (h != HALF_HEIGHT)
		g->p.y -= h - HALF_HEIGHT;
	if (g->p.y > HEIGHT)
		g->p.y = HEIGHT;
	if (g->p.y < -HEIGHT)
		g->p.y = -HEIGHT;
	mlx_mouse_move(g->mlx.mlx, g->mlx.win, HW, HALF_HEIGHT);
	return (0);
}
