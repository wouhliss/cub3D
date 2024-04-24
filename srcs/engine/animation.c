/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:28:01 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 19:32:19 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_animate_wall(t_game *g)
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
			g->wt[index].s = g->wt[index].f * g->wt[index].w * g->wt[index].w;
			g->wt[index].last = g->now;
		}
	}
}

static inline void	ft_animate_sprite(t_game *g)
{
	int	index;

	index = -1;
	while (++index < STEXTURES)
	{
		if (g->sframes[index] && g->now - g->st[index].last > g->sframes[index]
			* 1000000)
		{
			++g->st[index].f;
			if (g->st[index].f == g->st[index].frames)
				g->st[index].f = 0;
			g->st[index].s = g->st[index].f * g->st[index].w * g->st[index].w;
			g->st[index].last = g->now;
		}
	}
}

void	ft_animate(t_game *g)
{
	ft_animate_wall(g);
	ft_animate_sprite(g);
}
