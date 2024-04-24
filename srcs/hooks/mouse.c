/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:55:43 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_changestate(t_game *g, int button)
{
	const int	states[] = {0, 0, CUBES, SPRITES};

	if (button == 4)
	{
		++g->p.weapon.t;
		if (g->p.weapon.t > WEAPONS)
			g->p.weapon.t = 0;
		g->p.weapon.state = 0;
	}
	else if (button == 5)
	{
		--g->p.weapon.t;
		if (g->p.weapon.t < 0)
			g->p.weapon.t = WEAPONS;
		g->p.weapon.state = 0;
	}
	if (button == 2 && g->p.weapon.state < states[g->p.weapon.t])
		++g->p.weapon.state;
	else if (button == 2)
		g->p.weapon.state = 0;
}

static inline void	ft_break_block(t_game *g)
{
	if (g->p.look_pos.x < 1 || g->p.look_pos.y < 1
		|| g->p.look_pos.x >= g->w - 1 || g->p.look_pos.y >= g->length - 1)
		return ;
	g->m.m[g->p.look_pos.y][g->p.look_pos.x] = '0';
}

static inline void	ft_place_block(t_game *g)
{
	t_door		door;
	t_intvec	facing;
	char		block;

	facing = ft_get_facing_int(g->p.looking_side, g->p.look_pos);
	if (facing.y == (int)g->p.pos.y && facing.x == (int)g->p.pos.x)
		return ;
	block = ft_get_block(g);
	g->m.m[facing.y][facing.x] = block;
	if (block != 'D')
		return ;
	door = (t_door){.frame = 0, .pos = (t_intvec){facing.x, facing.y},
		.state = 0};
	ft_add_to_vector(g, &g->doors, &door);
}

int	on_mouse_click(int button, int x, int y, void *param)
{
	t_game		*game;

	(void)x;
	(void)y;
	game = param;
	if (button == 1 && game->p.weapon.t == 1)
		ft_add_projectile(game, game->p.pos, game->p.dir, 0);
	else if (button == 1 && game->p.weapon.t == 0)
		ft_add_projectile(game, game->p.pos, game->p.dir, 1);
	else if (button == 3 && game->p.weapon.t == 0)
		ft_add_projectile(game, game->p.pos, game->p.dir, 2);
	else if (button == 1 && game->p.looking && game->p.weapon.t == 2)
		ft_break_block(game);
	else if (button == 3 && game->p.looking && game->p.weapon.t == 2)
		ft_place_block(game);
	else if (button == 3 && game->p.weapon.t == 3)
		ft_place_sprite(game);
	else if (button == 2 || button == 4 || button == 5)
		ft_changestate(game, button);
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
