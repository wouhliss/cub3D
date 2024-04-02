/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:02:56 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/02 16:57:58 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_aim_h(t_game *game)
{
	double	x;

	if (game->turn_r)
	{
		x = game->p.dir.x;
		game->p.dir.x = x * cos(-(game->sens)) - game->p.dir.y
			* sin(-(game->sens));
		game->p.dir.y = x * sin(-(game->sens)) + game->p.dir.y
			* cos(-(game->sens));
		x = game->p.p.x;
		game->p.p.x = x * cos(-(game->sens)) - game->p.p.y * sin(-(game->sens));
		game->p.p.y = x * sin(-(game->sens)) + game->p.p.y * cos(-(game->sens));
	}
	if (game->turn_l)
	{
		x = game->p.dir.x;
		game->p.dir.x = x * cos((game->sens)) - game->p.dir.y
			* sin((game->sens));
		game->p.dir.y = x * sin((game->sens)) + game->p.dir.y
			* cos((game->sens));
		x = game->p.p.x;
		game->p.p.x = x * cos((game->sens)) - game->p.p.y * sin((game->sens));
		game->p.p.y = x * sin((game->sens)) + game->p.p.y * cos((game->sens));
	}
}

void	ft_aim(t_game *game)
{
	game->sens = 0.000000008 * game->delta;
	ft_aim_h(game);
	if (game->up && game->p.y < HEIGHT)
	{
		game->p.y += (0.000004 * game->delta);
		if (game->p.y > HEIGHT)
			game->p.y = HEIGHT;
	}
	if (game->down && game->p.y > -HEIGHT)
	{
		game->p.y -= (0.000004 * game->delta);
		if (game->p.y < -HEIGHT)
			game->p.y = -HEIGHT;
	}
}
