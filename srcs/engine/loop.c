/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:31:10 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 15:51:43 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_lsteps(t_game *game)
{
	game->p.looking = false;
	game->p.dd.x = fabs(1.0 / -game->p.dir.x);
	game->p.dd.y = fabs(1.0 / game->p.dir.y);
	game->p.map = (t_intvec){(int)game->p.pos.x, (int)game->p.pos.y};
	if (-game->p.dir.x < 0)
	{
		game->p.step.x = -1;
		game->p.sd.x = (game->p.pos.x - game->p.map.x) * game->p.dd.x;
	}
	else
	{
		game->p.step.x = 1;
		game->p.sd.x = (game->p.map.x + 1.0 - game->p.pos.x) * game->p.dd.x;
	}
	if (game->p.dir.y < 0)
	{
		game->p.step.y = -1;
		game->p.sd.y = (game->p.pos.y - game->p.map.y) * game->p.dd.y;
	}
	else
	{
		game->p.step.y = 1;
		game->p.sd.y = (game->p.map.y + 1.0 - game->p.pos.y) * game->p.dd.y;
	}
}

static inline void	ft_ldda(t_game *g)
{
	while (!g->p.looking && !ft_outside(g, g->p.map.x, g->p.map.y))
	{
		if (g->p.sd.x < g->p.sd.y)
		{
			g->p.sd.x += g->p.dd.x;
			g->p.map.x += g->p.step.x;
			g->p.pdist = g->p.sd.x - g->p.dd.x;
			g->p.looking_side = -1;
		}
		else
		{
			g->p.sd.y += g->p.dd.y;
			g->p.map.y += g->p.step.y;
			g->p.pdist = g->p.sd.y - g->p.dd.y;
			g->p.looking_side = 1;
		}
		if ((g->p.pdist > 3 || (int)(HEIGHT / g->p.pdist) <= fabs(g->p.y) * 2))
			break ;
		if (!ft_outside(g, g->p.map.x, g->p.map.y)
			&& g->map.map[g->p.map.y][g->p.map.x] != '0')
		{
			g->p.look_pos = (t_intvec){g->p.map.x, g->p.map.y};
			g->p.looking = true;
		}
	}
}

static inline void	ft_update_doors_portals(t_game *g)
{
	size_t		i;
	t_intvec	facing;

	if (g->p.looking_side < 0 && g->p.step.x < 0)
		g->p.looking_side = -2;
	if (g->p.looking_side > 0 && g->p.step.y < 0)
		g->p.looking_side = 2;
	i = 0;
	while (i < g->doors.index)
	{
		if (g->doors.u_ptr.d[i].delete || g->now
			- g->doors.u_ptr.d[i].last < 5000000)
		{
			++i;
			continue ;
		}
		ft_update_door(g, &g->doors.u_ptr.d[i]);
		if (g->map.map[g->doors.u_ptr.d[i].pos.y][g->doors.u_ptr.d[i].pos.x] != 'D'
			|| (!(g->map.map[g->doors.u_ptr.d[i].pos.y
					+ 1][g->doors.u_ptr.d[i].pos.x] == '1'
					&& g->map.map[g->doors.u_ptr.d[i].pos.y
					- 1][g->doors.u_ptr.d[i].pos.x] == '1')
				&& !(g->map.map[g->doors.u_ptr.d[i].pos.y][g->doors.u_ptr.d[i].pos.x
					+ 1] == '1'
					&& g->map.map[g->doors.u_ptr.d[i].pos.y][g->doors.u_ptr.d[i].pos.x
					- 1] == '1')))
			ft_remove_door(g, &g->doors.u_ptr.d[i]);
		++i;
	}
	if (g->map.map[g->portal_l.pos.y][g->portal_l.pos.x] != '1')
		g->portal_l.side = 0;
	if (g->map.map[g->portal_r.pos.y][g->portal_r.pos.x] != '1')
		g->portal_r.side = 0;
	facing = ft_get_facing_int(g->portal_l.side, g->portal_l.pos);
	if (g->map.map[facing.y][facing.x] != '0')
		g->portal_l.side = 0;
	facing = ft_get_facing_int(g->portal_r.side, g->portal_r.pos);
	if (g->map.map[facing.y][facing.x] != '0')
		g->portal_r.side = 0;
}

static inline void	ft_render_queue(t_game *g)
{
	int	i;

	i = -1;
	while (++i < THREADS)
	{
		g->threads[i].id = i;
		g->threads[i].g = g;
		g->threads[i].dx = T_WIDTH * i + (g->frames & 1);
		g->threads[i].x = T_WIDTH * (i + 1);
		if (!g->last)
			ft_create_vector(&g->threads[i].hit, HIT, sizeof(t_hit));
		pthread_create(&g->threads[i].tid, NULL, ft_draw, &g->threads[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(g->threads[i].tid, NULL);
	ft_drawmap(g);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->s.img, 0, 0);
}

static inline void	ft_animate(t_game *g)
{
	int	index;

	index = -1;
	while (++index < WTEXTURES)
	{
		if (g->wframes[index] && g->now - g->wt[index].last > g->wframes[index]
			* 1000000)
		{
			++g->wt[index].f;
			if (g->wt[index].f == g->wt[index].frames)
				g->wt[index].f = 0;
			g->wt[index].s = g->wt[index].f * g->wt[index].width
				* g->wt[index].width;
			g->wt[index].last = g->now;
		}
	}
	index = -1;
	while (++index < STEXTURES)
	{
		if (g->sframes[index] && g->now - g->st[index].last > g->sframes[index]
			* 1000000)
		{
			++g->st[index].f;
			if (g->st[index].f == g->st[index].frames)
				g->st[index].f = 0;
			g->st[index].s = g->st[index].f * g->st[index].width
				* g->st[index].width;
			g->st[index].last = g->now;
		}
	}
}

int	ft_loop(void *param)
{
	t_game			*game;
	struct timespec	t;

	game = param;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t);
	game->now = t.tv_nsec + t.tv_sec * 1000000000;
	if (game->now - game->f > 1000000000)
	{
		printf("fps: %d\n", game->frames);
		game->frames = 0;
		game->f = game->now;
	}
	game->delta = game->now - game->last;
	if (game->delta < 8000000)
		return (0);
	ft_animate(game);
	ft_handle_movement(game);
	ft_handle_aim(game);
	ft_lsteps(game);
	ft_ldda(game);
	ft_handle_pls(game);
	ft_update_doors_portals(game);
	ft_render_queue(game);
	game->last = game->now;
	++game->frames;
	return (0);
}
