/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:12:18 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/04 14:15:16 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	on_key_press(int k, void *param)
{
	t_game	*game;

	game = param;
	if (k == XK_Escape)
		return (mlx_loop_end(game->mlx.mlx), 0);
	else if (k == XK_W || k == XK_w || k == XK_Z || k == XK_z)
		game->front = 1;
	else if (k == XK_S || k == XK_s)
		game->back = 1;
	else if (k == XK_A || k == XK_a || k == XK_Q || k == XK_q)
		game->left = 1;
	else if (k == XK_D || k == XK_d)
		game->right = 1;
	else if (k == XK_Left)
		game->turn_l = 1;
	else if (k == XK_Right)
		game->turn_r = 1;
	else if (k == XK_Up)
		game->up = 1;
	else if (k == XK_Down)
		game->down = 1;
	else if (k == XK_space)
		game->p.jump = 500;
	return (0);
}

int	on_key_release(int k, void *param)
{
	t_game	*game;

	game = param;
	if (k == XK_W || k == XK_w || k == XK_Z || k == XK_z)
		game->front = 0;
	else if (k == XK_S || k == XK_s)
		game->back = 0;
	else if (k == XK_A || k == XK_a || k == XK_Q || k == XK_q)
		game->left = 0;
	else if (k == XK_D || k == XK_d)
		game->right = 0;
	else if (k == XK_Left)
		game->turn_l = 0;
	else if (k == XK_Right)
		game->turn_r = 0;
	else if (k == XK_Up)
		game->up = 0;
	else if (k == XK_Down)
		game->down = 0;
	else if (k == XK_Shift_L)
		game->shift = 0;
	else if (k == XK_space)
		game->p.jump = 0;
	return (0);
}
