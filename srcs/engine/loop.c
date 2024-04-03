/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:31:10 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 19:30:05 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline int	ft_get_state(t_game *game)
{
	int	state;

	pthread_mutex_lock(&game->state_m);
	state = game->state;
	pthread_mutex_unlock(&game->state_m);
	return (state);	
}

static inline void	ft_set_state(t_game *game, const int state)
{
	usleep(10);
	pthread_mutex_lock(&game->state_m);
	game->state = state;
	pthread_mutex_unlock(&game->state_m);
}

static inline int	ft_get_rendered(t_game *game, const int id)
{
	int	state;

	pthread_mutex_lock(&game->rendered_m[id]);
	state = game->rendered[id];
	pthread_mutex_unlock(&game->rendered_m[id]);
	return (state);
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
		printf("%d\n", game->frames);
		game->frames = 0;
		game->f = game->now;
	}
	++game->frames;
	ft_set_state(game, COMPUTING);
	game->delta = game->now - game->last;
	game->last = game->now;
	ft_set_state(game, RENDERING);
	i = 0;
	while (i < THREADS)
	{
		if (ft_get_rendered(game, i) == COMPLETED)
			++i;
		else
			usleep(10);
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->screen.img, 0,
		0);
	ft_set_state(game, DRAWN);
	i = -1;
	while (++i < THREADS)
	{
		pthread_mutex_lock(&game->rendered_m[i]);
		game->rendered[i] = TDRAWING;
		pthread_mutex_unlock(&game->rendered_m[i]);
	}
	return (0);
}
