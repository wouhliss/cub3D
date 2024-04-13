/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:12:18 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/13 14:07:36 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_interact(t_game *g)
{
	size_t	i;

	if (g->p.looking)
	{
		i = 0;
		while (i < g->doors.index)
		{
			if (g->doors.ptr.d[i].state == CLOSED
				&& g->doors.ptr.d[i].pos.x == g->p.look_pos.x
				&& g->doors.ptr.d[i].pos.y == g->p.look_pos.y)
				g->doors.ptr.d[i].state = OPENING;
			else if (g->doors.ptr.d[i].state == OPEN
				&& g->doors.ptr.d[i].pos.x == g->p.look_pos.x
				&& g->doors.ptr.d[i].pos.y == g->p.look_pos.y)
				g->doors.ptr.d[i].state = CLOSING;
			++i;
		}
	}
}

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
	else if (k == XK_Shift_L)
		game->shift = 1;
	else if (k == XK_E || k == XK_e)
		ft_interact(game);
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
	return (0);
}
