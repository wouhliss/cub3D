/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:31:10 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 22:52:41 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_ldda(t_game *g)
{
	while (!g->p.looking && !ft_outside(g, g->p.m.x, g->p.m.y))
	{
		if (g->p.sd.x < g->p.sd.y)
		{
			g->p.sd.x += g->p.dd.x;
			g->p.m.x += g->p.step.x;
			g->p.pdist = g->p.sd.x - g->p.dd.x;
			g->p.looking_side = -1;
		}
		else
		{
			g->p.sd.y += g->p.dd.y;
			g->p.m.y += g->p.step.y;
			g->p.pdist = g->p.sd.y - g->p.dd.y;
			g->p.looking_side = 1;
		}
		if ((g->p.pdist > 3 || (int)(HEIGHT / g->p.pdist) <= fabs(g->p.y) * 2))
			break ;
		if (!ft_outside(g, g->p.m.x, g->p.m.y)
			&& g->m.m[g->p.m.y][g->p.m.x] != '0')
		{
			g->p.look_pos = (t_intvec){g->p.m.x, g->p.m.y};
			g->p.looking = true;
		}
	}
}

static inline void	ft_lsteps(t_game *game)
{
	game->p.looking = false;
	game->p.dd.x = fabs(1.0 / -game->p.dir.x);
	game->p.dd.y = fabs(1.0 / game->p.dir.y);
	game->p.m = (t_intvec){(int)game->p.pos.x, (int)game->p.pos.y};
	if (-game->p.dir.x < 0)
	{
		game->p.step.x = -1;
		game->p.sd.x = (game->p.pos.x - game->p.m.x) * game->p.dd.x;
	}
	else
	{
		game->p.step.x = 1;
		game->p.sd.x = (game->p.m.x + 1.0 - game->p.pos.x) * game->p.dd.x;
	}
	if (game->p.dir.y < 0)
	{
		game->p.step.y = -1;
		game->p.sd.y = (game->p.pos.y - game->p.m.y) * game->p.dd.y;
	}
	else
	{
		game->p.step.y = 1;
		game->p.sd.y = (game->p.m.y + 1.0 - game->p.pos.y) * game->p.dd.y;
	}
	ft_ldda(game);
}

static inline void	ft_render_queue(t_game *g)
{
	g->threads[0].id = 0;
	g->threads[0].g = g;
	g->threads[0].dx = (g->frames & 1);
	g->threads[0].x = W;
	if (!g->last)
		ft_create_vector(&g->threads[0].hit, HIT, sizeof(t_hit));
	ft_draw(&g->threads[0]);
	ft_drawmap(g);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->s.img, 0, 0);
}

int	ft_loop(void *param)
{
	t_game			*game;

	game = param;
	game->delta = 3000000;
	game->now += 3000000;
	ft_animate(game);
	ft_handle_movement(game);
	ft_handle_aim(game);
	ft_lsteps(game);
	ft_handle_pls(game);
	ft_update_doors_portals(game);
	ft_render_queue(game);
	game->last = game->now;
	++game->frames;
	return (0);
}
