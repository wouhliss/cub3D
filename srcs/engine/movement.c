/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:02:00 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/02 12:55:16 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline bool	ft_door(t_game *game, int x, int y)
{
	t_door	*door;

	door = game->doors;
	while (door)
	{
		if (door->pos.x == x && door->pos.y == y)
			return (door->state == OPEN);
		door = door->next;
	}
	return (false);
}

static inline bool	ft_canmove(t_game *game, double x, double y)
{
	if (game->portal_l.pos.x == (int)x && game->portal_l.pos.y == (int)y)
	{
		if (game->portal_r.side)
		{
			game->p.pos.x = game->portal_r.pos.x + (game->p.pos.x - (int)game->p.pos.x);
			game->p.pos.y = game->portal_r.pos.y + (game->p.pos.y - (int)game->p.pos.y);
			return (true);
		}
	}
	if (game->portal_r.pos.x == (int)x && game->portal_r.pos.y == (int)y)
	{
		if (game->portal_l.side)
		{
			game->p.pos.x = game->portal_l.pos.x + (game->p.pos.x - (int)game->p.pos.x);
			game->p.pos.y = game->portal_l.pos.y + (game->p.pos.y - (int)game->p.pos.y);
			return (true);
		}
	}
	return (x >= 1.0 && y >= 1.0 && (int)x < game->width - 1 && (int)y < game->length - 1
		&& (game->map.map[(int)(y)][(int)(x)] == '0' || game->noclip || ft_door(game, (int)x, (int)y)));
}

static inline void	ft_handle_fb(t_game *game)
{
	if (game->front)
	{
		if (ft_canmove(game, game->p.pos.x + -game->p.dir.x * (game->speed
					+ game->speed * game->shift * 0.6), game->p.pos.y))
			game->p.pos.x += -game->p.dir.x * (game->speed + game->speed
					* game->shift * 0.6);
		if (ft_canmove(game, game->p.pos.x, game->p.pos.y + game->p.dir.y
				* (game->speed + game->speed * game->shift * 0.6)))
			game->p.pos.y += game->p.dir.y * (game->speed + game->speed
					* game->shift * 0.6);
	}
	if (game->back)
	{
		if (ft_canmove(game, game->p.pos.x - -game->p.dir.x * game->speed
				+ game->speed * game->shift * 0.6, game->p.pos.y))
			game->p.pos.x -= -game->p.dir.x * (game->speed + game->speed
					* game->shift * 0.6);
		if (ft_canmove(game, game->p.pos.x, game->p.pos.y - game->p.dir.y
				* (game->speed + game->speed * game->shift * 0.6)))
			game->p.pos.y -= game->p.dir.y * (game->speed + game->speed
					* game->shift * 0.6);
	}
}

void	ft_move(t_game *game)
{
	game->speed = (game->delta * 0.000000003);
	ft_handle_fb(game);
	if (game->right)
	{
		if (ft_canmove(game, game->p.pos.x - game->p.dir.y * (game->speed
					+ game->speed * game->shift * 0.6), game->p.pos.y))
			game->p.pos.x -= game->p.dir.y * (game->speed + game->speed
					* game->shift * 0.6);
		if (ft_canmove(game, game->p.pos.x, game->p.pos.y + -game->p.dir.x
				* (game->speed + game->speed * game->shift * 0.6)))
			game->p.pos.y += -game->p.dir.x * (game->speed + game->speed
					* game->shift * 0.6);
	}
	if (game->left)
	{
		if (ft_canmove(game, game->p.pos.x + game->p.dir.y * (game->speed
					+ game->speed * game->shift * 0.6), game->p.pos.y))
			game->p.pos.x += game->p.dir.y * (game->speed + game->speed
					* game->shift * 0.6);
		if (ft_canmove(game, game->p.pos.x, game->p.pos.y - -game->p.dir.x
				* (game->speed + game->speed * game->shift * 0.6)))
			game->p.pos.y -= -game->p.dir.x * (game->speed + game->speed
					* game->shift * 0.6);
	}
}
