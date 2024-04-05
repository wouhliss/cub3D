/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:03:45 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/05 11:22:42 by wouhliss         ###   ########.fr       */
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

void	ft_handle_aim(t_game *g)
{
	g->sens = 0.000000004 * g->delta;
	ft_aim_h(g);
	if (g->up && g->p.y < HEIGHT)
	{
		g->p.y += (0.000002 * g->delta);
		if (g->p.y > HEIGHT)
			g->p.y = HEIGHT;
	}
	if (g->down && g->p.y > -HEIGHT)
	{
		g->p.y -= (0.000002 * g->delta);
		if (g->p.y < -HEIGHT)
			g->p.y = -HEIGHT;
	}
}
