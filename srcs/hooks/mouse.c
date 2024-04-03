/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 17:26:53 by wouhliss         ###   ########.fr       */
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
	t_game		*game;

	(void)x;
	(void)y;
	game = param;
	if (button == 4)
	{
		++game->p.weapon.type;
		if (game->p.weapon.type > 3)
			game->p.weapon.type = 0;
		game->p.weapon.state = 0;
	}
	else if (button == 5)
	{
		--game->p.weapon.type;
		if (game->p.weapon.type < 0)
			game->p.weapon.type = 3;
		game->p.weapon.state = 0;
	}
	else if (button == 1 && game->p.looking && game->p.weapon.type == 2)
	{
		if (game->p.look_pos.y == game->portal_l.pos.y
			&& game->p.look_pos.x == game->portal_l.pos.x)
			game->portal_l.side = 0;
		else if (game->p.look_pos.y == game->portal_r.pos.y
			&& game->p.look_pos.x == game->portal_r.pos.x)
			game->portal_r.side = 0;
		game->map.map[game->p.look_pos.y][game->p.look_pos.x] = '0';
		if (game->map.map[game->p.look_pos.y + 1][game->p.look_pos.x] == 'D')
			game->map.map[game->p.look_pos.y + 1][game->p.look_pos.x] = '0';
		else if (game->map.map[game->p.look_pos.y - 1][game->p.look_pos.x] == 'D')
			game->map.map[game->p.look_pos.y - 1][game->p.look_pos.x] = '0';
		else if (game->map.map[game->p.look_pos.y][game->p.look_pos.x + 1] == 'D')
			game->map.map[game->p.look_pos.y][game->p.look_pos.x + 1] = '0';
		else if (game->map.map[game->p.look_pos.y][game->p.look_pos.x - 1] == 'D')
			game->map.map[game->p.look_pos.y][game->p.look_pos.x - 1] = '0';
	}
	else if (button == 3 && game->p.looking && game->p.weapon.type == 2)
	{
		if (game->p.looking_side == -2
			&& ((int)game->p.pos.x != game->p.look_pos.x + 1
				|| (int)game->p.pos.y != game->p.look_pos.y))
			game->map.map[game->p.look_pos.y][game->p.look_pos.x + 1] = game->p.weapon.state ? 't' : '1';
		else if (game->p.looking_side == -1
			&& ((int)game->p.pos.x != game->p.look_pos.x - 1
				|| (int)game->p.pos.y != game->p.look_pos.y))
			game->map.map[game->p.look_pos.y][game->p.look_pos.x - 1] = game->p.weapon.state ? 't' : '1';
		else if (game->p.looking_side == 2
			&& ((int)game->p.pos.x != game->p.look_pos.x
				|| (int)game->p.pos.y != game->p.look_pos.y + 1))
			game->map.map[game->p.look_pos.y + 1][game->p.look_pos.x] = game->p.weapon.state ? 't' : '1';
		else if (game->p.looking_side == 1
			&& ((int)game->p.pos.x != game->p.look_pos.x
				|| (int)game->p.pos.y != game->p.look_pos.y - 1))
			game->map.map[game->p.look_pos.y - 1][game->p.look_pos.x] = game->p.weapon.state ? 't' : '1';
		if (game->p.looking_side == game->portal_l.side && game->portal_l.pos.x == game->p.look_pos.x && game->portal_l.pos.y == game->p.look_pos.y)
			game->portal_l.side = 0;
		else if (game->p.looking_side == game->portal_r.side && game->portal_r.pos.x == game->p.look_pos.x && game->portal_r.pos.y == game->p.look_pos.y)
			game->portal_r.side = 0;
	}
	else if (button == 2)
		ft_changestate(&game->p.weapon);
	return (0);
}

int	on_mouse_move(int w, int h, void *param)
{
	t_game	*game;
	double	x;
	double	y;

	if (w == HALF_WIDTH && h == HALF_HEIGHT)
		return (0);
	game = param;
	x = game->p.dir.x;
	y = game->p.dir.y;
	game->p.dir.x = x * cos((HALF_WIDTH - w) * 0.0015) - y * sin((HALF_WIDTH
				- w) * 0.0015);
	game->p.dir.y = x * sin((HALF_WIDTH - w) * 0.0015) + y * cos((HALF_WIDTH
				- w) * 0.0015);
	x = game->p.p.x;
	y = game->p.p.y;
	game->p.p.x = x * cos((HALF_WIDTH - w) * 0.0015) - y * sin((HALF_WIDTH - w)
			* 0.0015);
	game->p.p.y = x * sin((HALF_WIDTH - w) * 0.0015) + y * cos((HALF_WIDTH - w)
			* 0.0015);
	if (h != HALF_HEIGHT)
		game->p.y -= h - HALF_HEIGHT;
	if (game->p.y > HEIGHT)
		game->p.y = HEIGHT;
	if (game->p.y < -HEIGHT)
		game->p.y = -HEIGHT;
	mlx_mouse_move(game->mlx.mlx, game->mlx.win, HALF_WIDTH, HALF_HEIGHT);
	return (0);
}
