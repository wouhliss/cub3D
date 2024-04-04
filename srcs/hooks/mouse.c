/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/04 13:17:37 by wouhliss         ###   ########.fr       */
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
	t_game	*game;
	float	x;
	float	y;

	if (w == HW && h == HALF_HEIGHT)
		return (0);
	game = param;
	x = game->p.dir.x;
	y = game->p.dir.y;
	game->p.dir.x = x * cos((HW - w) * 0.0015) - y * sin((HW - w) * 0.0015);
	game->p.dir.y = x * sin((HW - w) * 0.0015) + y * cos((HW - w) * 0.0015);
	x = game->p.p.x;
	y = game->p.p.y;
	game->p.p.x = x * cos((HW - w) * 0.0015) - y * sin((HW - w) * 0.0015);
	game->p.p.y = x * sin((HW - w) * 0.0015) + y * cos((HW - w) * 0.0015);
	if (h != HALF_HEIGHT)
		game->p.y -= h - HALF_HEIGHT;
	if (game->p.y > HEIGHT)
		game->p.y = HEIGHT;
	if (game->p.y < -HEIGHT)
		game->p.y = -HEIGHT;
	mlx_mouse_move(game->mlx.mlx, game->mlx.win, HW, HALF_HEIGHT);
	return (0);
}
