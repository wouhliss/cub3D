/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:12:18 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/30 06:12:28 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	on_key_press(int k, void *param)
{
	t_game		*game;

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
			game->p.plane = game->psprite->plane;
		}
		else
		{
			game->psprite->pos = game->p.pos;
			game->psprite->dir = game->p.dir;
			game->psprite->plane = game->p.plane;
			game->psprite->hide = 0;
		}
		game->noclip ^= 1;
	}
	else if (k == XK_3)
	{
		t_sprite	sprite;

		sprite = (t_sprite){.type = 0, .vdiff = 64.0, .hr = 1,
				.vr = 1, .hide = 0, .pos = game->p.pos};
		ft_addsprite(game, &sprite);
		ft_loadsprites(game);
	}
	else if (k == XK_4)
	{
		ft_addprojectile(game, game->p.pos, game->p.dir);
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
