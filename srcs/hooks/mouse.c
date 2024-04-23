/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:35:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/23 11:37:23 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_changestate(t_game *g, int button)
{
	const int	states[] = {0, 0, CUBES, SPRITES};

	if (button == 4)
	{
		++g->p.weapon.type;
		if (g->p.weapon.type > WEAPONS)
			g->p.weapon.type = 0;
		g->p.weapon.state = 0;
	}
	else if (button == 5)
	{
		--g->p.weapon.type;
		if (g->p.weapon.type < 0)
			g->p.weapon.type = WEAPONS;
		g->p.weapon.state = 0;
	}
	else if (g->p.weapon.state < states[g->p.weapon.type])
		++g->p.weapon.state;
	else
		g->p.weapon.state = 0;
}

static inline void	ft_break_block(t_game *g)
{
	if (g->p.look_pos.x < 1 || g->p.look_pos.y < 1
		|| g->p.look_pos.x >= g->width - 1 || g->p.look_pos.y >= g->length - 1)
		return ;
	g->map.map[g->p.look_pos.y][g->p.look_pos.x] = '0';
}

static inline void	ft_place_block(t_game *g)
{
	t_door	door;
	int		x;
	int		y;
	char	block;

	x = g->p.look_pos.x;
	y = g->p.look_pos.y;
	if (g->p.looking_side == -2)
		++x;
	else if (g->p.looking_side == -1)
		--x;
	else if (g->p.looking_side == 2)
		++y;
	else if (g->p.looking_side == 1)
		--y;
	if (y == (int)g->p.pos.y && x == (int)g->p.pos.x)
		return ;
	block = ft_get_block(g);
	g->map.map[y][x] = block;
	if (block != 'D')
		return ;
	door = (t_door){.frame = 0, .pos = (t_intvec){x, y}, .state = 0};
	ft_add_to_vector(g, &g->doors, &door);
}

int	on_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;

	(void)x;
	(void)y;
	game = param;
	if (button == 1 && game->p.weapon.type == 1)
		ft_add_projectile(game, game->p.pos, game->p.dir, 0);
	else if (button == 1 && game->p.weapon.type == 0)
		ft_add_projectile(game, game->p.pos, game->p.dir, 1);
	else if (button == 3 && game->p.weapon.type == 0)
		ft_add_projectile(game, game->p.pos, game->p.dir, 2);
	else if (button == 1 && game->p.looking && game->p.weapon.type == 2)
		ft_break_block(game);
	else if (button == 3 && game->p.looking && game->p.weapon.type == 2)
		ft_place_block(game);
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
