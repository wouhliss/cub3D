/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/22 02:58:14 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	on_mouse(int w, int h, void *param)
{
	t_game	*game;
	double	x;
	double	y;

	game = param;
	x = game->p.dir.x;
	y = game->p.dir.y;
	game->p.dir.x = x * cos((WIDTH / 2 - w) * 0.0015) - y * sin((WIDTH / 2 - w)
			* 0.0015);
	game->p.dir.y = x * sin((WIDTH / 2 - w) * 0.0015) + y * cos((WIDTH / 2 - w)
			* 0.0015);
	x = game->p.plane.x;
	y = game->p.plane.y;
	game->p.plane.x = x * cos((WIDTH / 2 - w) * 0.0015) - y * sin((WIDTH / 2
				- w) * 0.0015);
	game->p.plane.y = x * sin((WIDTH / 2 - w) * 0.0015) + y * cos((WIDTH / 2
				- w) * 0.0015);
	game->p.y = ( h - HEIGHT / 2)  * -1;

	if (game->p.y > HEIGHT)
		game->p.y = HEIGHT;
	else if (game->p.y < -HEIGHT)
		game->p.y = -HEIGHT;
	mlx_mouse_move(game->mlx.mlx, game->mlx.win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
