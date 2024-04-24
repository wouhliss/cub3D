/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:08:21 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 20:03:37 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_player(char c, int i, int j, t_game *game)
{
	game->m.s_dir = c;
	game->m.s_pos = (t_vec){j + 0.5, i + 0.5};
	game->p.pos = (t_vec){j + 0.5, i + 0.5};
	if (c == 'N')
	{
		game->p.dir = (t_vec){0, -1};
		game->p.p = (t_vec){-0.66, 0};
	}
	else if (c == 'S')
	{
		game->p.dir = (t_vec){0, 1};
		game->p.p = (t_vec){0.66, 0};
	}
	else if (c == 'W')
	{
		game->p.dir = (t_vec){1, 0};
		game->p.p = (t_vec){0, -0.66};
	}
	else if (c == 'E')
	{
		game->p.dir = (t_vec){-1, 0};
		game->p.p = (t_vec){0, 0.66};
	}
	game->m.m[i][j] = '0';
}

static inline void	ft_setsprite(t_game *game, int i, int j)
{
	t_sprite	sprite;

	if (game->m.m[i][j] == 'b')
	{
		sprite = (t_sprite){.t = 1, .vdiff = 0.0, .hr = 2, .vr = 2, .hide = 0,
			.collision = 1, .delete = false};
		sprite.pos = (t_vec){j + 0.5, i + 0.5};
		sprite.vdiff = HEIGHT / (sprite.vr * 2);
		game->m.m[i][j] = '0';
	}
	else if (game->m.m[i][j] == 'B')
	{
		sprite = (t_sprite){.t = 1, .vdiff = 0.0, .hr = 1, .vr = 1, .hide = 0,
			.collision = 1, .delete = false};
		sprite.pos = (t_vec){j + 0.5, i + 0.5};
		game->m.m[i][j] = '0';
	}
	else if (game->m.m[i][j] == 'P')
	{
		sprite = (t_sprite){.t = 0, .vdiff = 0.0, .hr = 1, .vr = 1, .hide = 0,
			.collision = 1, .delete = false};
		sprite.pos = (t_vec){j + 0.5, i + 0.5};
		game->m.m[i][j] = '0';
	}
	ft_add_to_vector(game, &game->sprites, &sprite);
}

static inline void	ft_add_door(t_game *g, const int i, const int j)
{
	t_door	door;

	door = (t_door){.frame = 0, .pos = (t_intvec){j, i}, .state = 0};
	ft_add_to_vector(g, &g->doors, &door);
}

int	check_one(t_game *g, int i, int j, int *player_count)
{
	if (i == 0 || i == g->length - 1 || j == 0 || j == g->w - 1)
		return (ic("12 ", g->m.m[i][j]));
	if (g->m.m[i][j] == '2')
		return (ic("12", g->m.m[i + 1][j]) && ic("12", g->m.m[i][j + 1]));
	else if (g->m.m[i][j] == '0')
		return (ic("01NSEWPbBtsD", g->m.m[i + 1][j]) && ic("01NSEWPbBtsD",
				g->m.m[i][j + 1]));
	else if (ic("PbB", g->m.m[i][j]))
	{
		ft_setsprite(g, i, j);
		return (ic("01NSEWPbBtDs", g->m.m[i + 1][j]) && ic("01NSEWPbBtsD",
				g->m.m[i][j + 1]));
	}
	else if (ic("D", g->m.m[i][j]))
		return (ft_add_door(g, i, j), ic("01NSEWPbBtDs", g->m.m[i + 1][j]) &&
		ic("01NSEWPbBtDs", g->m.m[i][j + 1]));
	else if (ic("NSEW", g->m.m[i][j]))
	{
		set_player(g->m.m[i][j], i, j, g);
		++(*player_count);
		return (ic("01PbBtDs", g->m.m[i + 1][j]) && ic("01PbBtDs", g->m.m[i][j
				+ 1]));
	}
	return (1);
}

int	check_map(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (game->m.m[i])
	{
		j = 0;
		while (game->m.m[i][j])
		{
			if (!ic("012NSEWPbBtsD", game->m.m[i][j]))
				return (0);
			if (!check_one(game, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
