/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:12:18 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/23 17:21:13 by wouhliss         ###   ########.fr       */
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
			if (g->doors.u_ptr.d[i].state == CLOSED
				&& g->doors.u_ptr.d[i].pos.x == g->p.look_pos.x
				&& g->doors.u_ptr.d[i].pos.y == g->p.look_pos.y)
				g->doors.u_ptr.d[i].state = OPENING;
			else if (g->doors.u_ptr.d[i].state == OPEN
				&& g->doors.u_ptr.d[i].pos.x == g->p.look_pos.x
				&& g->doors.u_ptr.d[i].pos.y == g->p.look_pos.y)
				g->doors.u_ptr.d[i].state = CLOSING;
			++i;
		}
	}
}

static inline void	ft_handle_mkey(t_game *g, int k)
{
	if (k == XK_W || k == XK_w || k == XK_Z || k == XK_z)
		g->front = 1;
	else if (k == XK_S || k == XK_s)
		g->back = 1;
	else if (k == XK_A || k == XK_a || k == XK_Q || k == XK_q)
		g->left = 1;
	else if (k == XK_D || k == XK_d)
		g->right = 1;
	else if (k == XK_Left)
		g->turn_l = 1;
	else if (k == XK_Right)
		g->turn_r = 1;
	else if (k == XK_Up)
		g->up = 1;
	else if (k == XK_Down)
		g->down = 1;
	else if (k == XK_Shift_L)
		g->shift = 1;
}

int	on_key_press(int k, void *param)
{
	t_game	*game;

	game = param;
	if (k == XK_Escape)
		return (mlx_loop_end(game->mlx.mlx), 0);
	else if (k == XK_E || k == XK_e)
		ft_interact(game);
	else if (k == XK_space)
		game->space = 1;
	else if (k == XK_j || k == XK_J)
	{
		game->s.lratio -= 0.01;
		game->s.rratio += 0.01;
	}
	else if (k == XK_k || k == XK_K)
	{
		game->s.lratio += 0.01;
		game->s.rratio -= 0.01;
	}
	else if (k == XK_p || k == XK_P)
	{
	}
	ft_handle_mkey(game, k);
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
		game->space = 0;
	return (0);
}
