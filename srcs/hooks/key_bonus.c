/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:12:18 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 11:33:23 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	on_key_press(int k, void *param)
{
	t_game	*game;
	t_door	*door;

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
	else if (k == 65453)
		game->minus = 1;
	else if (k == 65451)
		game->plus = 1;
	else if (k == XK_Shift_L)
		game->shift = 1;
	else if (k == XK_1)
		game->hsprite ^= 1;
	else if (k == XK_2)
	{
		if (game->noclip)
		{
			game->psprite->hide = 1;
			game->p.pos = game->psprite->pos;
			game->p.dir = game->psprite->dir;
			game->p.p = game->psprite->plane;
		}
		else
		{
			game->psprite->pos = game->p.pos;
			game->psprite->dir = game->p.dir;
			game->psprite->plane = game->p.p;
			game->psprite->hide = 0;
		}
		game->noclip ^= 1;
	}
	else if (k == XK_space && game->p.jumping == GROUND)
		game->p.jumping = JUMPING;
	else if ((k == XK_e || k == XK_E) && game->p.looking
		&& game->map.map[game->p.look_pos.y][game->p.look_pos.x] == 'D')
	{
		door = game->doors;
		while (door)
		{
			if (door->pos.x == game->p.look_pos.x
				&& door->pos.y == game->p.look_pos.y)
			{
				if (door->state == CLOSED)
					door->state = OPENING;
				else if (door->state == OPEN)
					door->state = CLOSING;
				break ;
			}
			door = door->next;
		}
		game->p.looking = false;
	}
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
	else if (k == 65453)
		game->minus = 0;
	else if (k == 65451)
		game->plus = 0;
	else if (k == XK_Shift_L)
		game->shift = 0;
	return (0);
}
