/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:59:22 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 18:59:29 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline int	ft_check_state(t_game *game)
{
	int	state;

	usleep(10);
	pthread_mutex_lock(&game->state_m);
	state = game->state;
	pthread_mutex_unlock(&game->state_m);
	return (state);
}

static inline int	ft_check_rstate(t_game *game, const int id)
{
	int	rstate;

	usleep(10);
	pthread_mutex_lock(&game->rendered_m[id]);
	rstate = game->rendered[id];
	pthread_mutex_unlock(&game->rendered_m[id]);
	return (rstate);
}

static inline void	ft_change_rstate(t_game *game, const int id,
		const int state)
{
	usleep(10);
	pthread_mutex_lock(&game->rendered_m[id]);
	game->rendered[id] = state;
	pthread_mutex_unlock(&game->rendered_m[id]);
}

void	*ft_thread(void *arg)
{
	t_thread	*t;
	t_game		*game;

	t = arg;
	game = t->game;
	while (ft_check_state(game) != ENDED)
	{
		while (ft_check_state(game) != RENDERING || game->rendered[t->id])
			if (ft_check_state(game) == ENDED)
				return (NULL);
		ft_draw(game, (t->id + 1) * T_WIDTH, t->id * T_WIDTH);
		ft_change_rstate(game, t->id, COMPLETED);
	}
	return (NULL);
}