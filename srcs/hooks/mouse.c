/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 00:00:15 by wouhliss         ###   ########.fr       */
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

static inline void	ft_break_block(t_game *g)
{
	if (g->p.look_pos.x < 1 || g->p.look_pos.y < 1
		|| g->p.look_pos.x >= g->width - 1 || g->p.look_pos.y >= g->length - 1)
		return ;
	if (g->p.look_pos.y == g->portal_l.pos.y
		&& g->p.look_pos.x == g->portal_l.pos.x)
		g->portal_l.side = 0;
	else if (g->p.look_pos.y == g->portal_r.pos.y
		&& g->p.look_pos.x == g->portal_r.pos.x)
		g->portal_r.side = 0;
	if (g->map.map[g->p.look_pos.y][g->p.look_pos.x] == 'D')
	{
		ft_remove_door(g, g->p.look_pos.x, g->p.look_pos.y);
		return ;
	}
	g->map.map[g->p.look_pos.y][g->p.look_pos.x] = '0';
	if (g->map.map[g->p.look_pos.y + 1][g->p.look_pos.x] == 'D')
		ft_remove_door(g, g->p.look_pos.x, g->p.look_pos.y + 1);
	else if (g->map.map[g->p.look_pos.y - 1][g->p.look_pos.x] == 'D')
		ft_remove_door(g, g->p.look_pos.x, g->p.look_pos.y - 1);
	else if (g->map.map[g->p.look_pos.y][g->p.look_pos.x + 1] == 'D')
		ft_remove_door(g, g->p.look_pos.x + 1, g->p.look_pos.y);
	else if (g->map.map[g->p.look_pos.y][g->p.look_pos.x - 1] == 'D')
		ft_remove_door(g, g->p.look_pos.x - 1, g->p.look_pos.y);
}

static inline void	ft_place_block(t_game *g)
{
	if (g->p.looking_side == -2 && ((int)g->p.pos.x != g->p.look_pos.x + 1
			|| (int)g->p.pos.y != g->p.look_pos.y))
		g->map.map[g->p.look_pos.y][g->p.look_pos.x + 1] = ft_get_block(g);
	else if (g->p.looking_side == -1 && ((int)g->p.pos.x != g->p.look_pos.x - 1
			|| (int)g->p.pos.y != g->p.look_pos.y))
		g->map.map[g->p.look_pos.y][g->p.look_pos.x - 1] = ft_get_block(g);
	else if (g->p.looking_side == 2 && ((int)g->p.pos.x != g->p.look_pos.x
			|| (int)g->p.pos.y != g->p.look_pos.y + 1))
		g->map.map[g->p.look_pos.y + 1][g->p.look_pos.x] = ft_get_block(g);
	else if (g->p.looking_side == 1 && ((int)g->p.pos.x != g->p.look_pos.x
			|| (int)g->p.pos.y != g->p.look_pos.y - 1))
		g->map.map[g->p.look_pos.y - 1][g->p.look_pos.x] = ft_get_block(g);
	if (g->p.looking_side == g->portal_l.side
		&& g->portal_l.pos.x == g->p.look_pos.x
		&& g->portal_l.pos.y == g->p.look_pos.y)
		g->portal_l.side = 0;
	else if (g->p.looking_side == g->portal_r.side
		&& g->portal_r.pos.x == g->p.look_pos.x
		&& g->portal_r.pos.y == g->p.look_pos.y)
		g->portal_r.side = 0;
}

int	on_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;

	(void)x;
	(void)y;
	game = param;
	if (button == 1 && game->p.looking && game->p.weapon.type == 2)
		ft_break_block(game);
	else if (button == 3 && game->p.looking && game->p.weapon.type == 2)
		ft_place_block(game);
	else if (button == 4)
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
	else if (button == 2)
		ft_changestate(&game->p.weapon);
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
	g->p.dir.x = x * cos((HW - w) * 0.00065) - y * sin((HW - w) * 0.00065);
	g->p.dir.y = x * sin((HW - w) * 0.00065) + y * cos((HW - w) * 0.00065);
	x = g->p.p.x;
	y = g->p.p.y;
	g->p.p.x = x * cos((HW - w) * 0.00065) - y * sin((HW - w) * 0.00065);
	g->p.p.y = x * sin((HW - w) * 0.00065) + y * cos((HW - w) * 0.00065);
	if (h != HALF_HEIGHT)
		g->p.y -= (h - HALF_HEIGHT) * 0.65;
	if (g->p.y > HEIGHT)
		g->p.y = HEIGHT;
	if (g->p.y < -HEIGHT)
		g->p.y = -HEIGHT;
	mlx_mouse_move(g->mlx.mlx, g->mlx.win, HW, HALF_HEIGHT);
	return (0);
}
