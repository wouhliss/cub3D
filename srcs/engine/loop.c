/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:31:10 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/14 11:52:08 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_steps(t_game *game)
{
	game->p.delta_dist = (t_vec){1e30, 1e30};
	if (-game->p.dir.x)
		game->p.delta_dist.x = fabs(1.0 / -game->p.dir.x);
	if (game->p.dir.y)
		game->p.delta_dist.y = fabs(1.0 / game->p.dir.y);
	game->p.map = (t_intvec){(int)game->p.pos.x, (int)game->p.pos.y};
	if (-game->p.dir.x < 0)
	{
		game->p.step.x = -1;
		game->p.side_dist.x = (game->p.pos.x - game->p.map.x)
			* game->p.delta_dist.x;
	}
	else
	{
		game->p.step.x = 1;
		game->p.side_dist.x = (game->p.map.x + 1.0 - game->p.pos.x)
			* game->p.delta_dist.x;
	}
	if (game->p.dir.y < 0)
	{
		game->p.step.y = -1;
		game->p.side_dist.y = (game->p.pos.y - game->p.map.y)
			* game->p.delta_dist.y;
	}
	else
	{
		game->p.step.y = 1;
		game->p.side_dist.y = (game->p.map.y + 1.0 - game->p.pos.y)
			* game->p.delta_dist.y;
	}
}

static inline void	ft_dda(t_game *game)
{
	while (!game->p.looking && !ft_outside(game, game->p.map.x, game->p.map.y))
	{
		if (game->p.side_dist.x < game->p.side_dist.y)
		{
			game->p.side_dist.x += game->p.delta_dist.x;
			game->p.map.x += game->p.step.x;
			game->p.pdist = game->p.side_dist.x - game->p.delta_dist.x;
			game->p.looking_side = -1;
			if (game->p.step.x < 0)
				game->p.looking_side = -2;
		}
		else
		{
			game->p.side_dist.y += game->p.delta_dist.y;
			game->p.map.y += game->p.step.y;
			game->p.pdist = game->p.side_dist.y - game->p.delta_dist.y;
			game->p.looking_side = 1;
			if (game->p.step.y < 0)
				game->p.looking_side = 2;
		}
		if (game->p.pdist > 3 || (int)(HEIGHT
				/ game->p.pdist) <= fabs(game->p.y) * 2)
			break ;
		if (!ft_outside(game, game->p.map.x, game->p.map.y)
			&& game->map.map[game->p.map.y][game->p.map.x] != '0')
		{
			game->p.look_pos = (t_intvec){game->p.map.x, game->p.map.y};
			game->p.looking = true;
		}
	}
}

int	ft_loop(void *param)
{
	t_game			*game;
	int				i;
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
	for (size_t i = 0; i < game->doors.index; ++i)
	{
		if (game->now - game->doors.ptr.d[i].last < 5000000)
			continue ;
		if (game->doors.ptr.d[i].state == OPENING)
			game->doors.ptr.d[i].frame += 0.01 * (game->now
					- game->doors.ptr.d[i].last) / 5000000;
		if (game->doors.ptr.d[i].frame >= 1.0
			&& game->doors.ptr.d[i].state == OPENING)
			game->doors.ptr.d[i].state = OPEN;
		if (game->doors.ptr.d[i].state == CLOSING)
			game->doors.ptr.d[i].frame -= 0.01 * (game->now
					- game->doors.ptr.d[i].last) / 5000000;
		if (game->doors.ptr.d[i].frame <= 0.0
			&& game->doors.ptr.d[i].state == CLOSING)
			game->doors.ptr.d[i].state = CLOSED;
		game->doors.ptr.d[i].last = game->now;
	}
	ft_handle_movement(game);
	ft_handle_aim(game);
	game->p.looking = false;
	ft_steps(game);
	ft_dda(game);
	i = -1;
	while (++i < THREADS)
	{
		game->threads[i].id = i;
		game->threads[i].g = game;
		if (!game->last)
			ft_create_vector(&game->threads[i].hit, HIT, sizeof(t_hit));
		pthread_create(&game->threads[i].tid, NULL, ft_draw, &game->threads[i]);
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(game->threads[i].tid, NULL);
	ft_drawmap(game);
	if (game->last)
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->s.img, 0,
			0);
	game->last = game->now;
	++game->frames;
	return (0);
}
