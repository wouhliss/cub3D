/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/01 15:47:11 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	on_mouse(int w, int h, void *param)
{
	t_game	*game;
	double	x;
	double	y;

	if (w == HALF_WIDTH && h == HALF_HEIGHT)
		return (0);
	game = param;
	x = game->p.dir.x;
	y = game->p.dir.y;
	game->p.dir.x = x * cos((HALF_WIDTH - w) * 0.0015) - y * sin((HALF_WIDTH - w)
			* 0.0015);
	game->p.dir.y = x * sin((HALF_WIDTH - w) * 0.0015) + y * cos((HALF_WIDTH - w)
			* 0.0015);
	x = game->p.p.x;
	y = game->p.p.y;
	game->p.p.x = x * cos((HALF_WIDTH - w) * 0.0015) - y * sin((HALF_WIDTH
				- w) * 0.0015);
	game->p.p.y = x * sin((HALF_WIDTH - w) * 0.0015) + y * cos((HALF_WIDTH
				- w) * 0.0015);
	if (h != HALF_HEIGHT)
		game->p.y -= h - HALF_HEIGHT;
	if (game->p.y > HEIGHT)
		game->p.y = HEIGHT;
	if (game->p.y < -HEIGHT)
		game->p.y = -HEIGHT;
	mlx_mouse_move(game->mlx.mlx, game->mlx.win, HALF_WIDTH, HALF_HEIGHT);
	return (0);
}
