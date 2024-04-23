/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:08:21 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/23 09:50:16 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_in_charset(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		++charset;
	}
	return (0);
}

void	set_player(char c, int i, int j, t_game *game)
{
	t_sprite	sprite;

	game->map.s_dir = c;
	game->map.s_pos = (t_vec){j + 0.5, i + 0.5};
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
	sprite = (t_sprite){.type = 3, .vdiff = 0.0, .hr = 1, .vr = 1, .hide = 1, .collision = 0};
	sprite.pos = game->map.s_pos;
	ft_add_to_vector(game, &game->sprites, &sprite);
	game->map.map[i][j] = '0';
}

static inline void	ft_setsprite(t_game *game, int i, int j)
{
	t_sprite	sprite;

	if (game->map.map[i][j] == 'b')
	{
		sprite = (t_sprite){.type = 2, .vdiff = 0.0, .hr = 2, .vr = 2,
			.hide = 0, .collision = 1};
		sprite.pos = (t_vec){j + 0.5, i + 0.5};
		sprite.vdiff = HEIGHT / (sprite.vr * 2);
		game->map.map[i][j] = '0';
	}
	else if (game->map.map[i][j] == 'B')
	{
		sprite = (t_sprite){.type = 1, .vdiff = 0.0, .hr = 1, .vr = 1,
			.hide = 0, .collision = 1};
		sprite.pos = (t_vec){j + 0.5, i + 0.5};
		game->map.map[i][j] = '0';
	}
	else if (game->map.map[i][j] == 'P')
	{
		sprite = (t_sprite){.type = 0, .vdiff = 0.0, .hr = 1, .vr = 1,
			.hide = 0, .collision = 1};
		sprite.pos = (t_vec){j + 0.5, i + 0.5};
		game->map.map[i][j] = '0';
	}
	ft_add_to_vector(game, &game->sprites, &sprite);
}

int	check_one(t_game *game, int i, int j, int *player_count)
{
	t_door	door;

	if (i == 0 || i == game->length - 1 || j == 0 || j == game->width - 1)
		return (ft_in_charset("12 ", game->map.map[i][j]));
	if (game->map.map[i][j] == '2')
		return (ft_in_charset("12", game->map.map[i + 1][j])
			&& ft_in_charset("12", game->map.map[i][j + 1]));
	else if (game->map.map[i][j] == '0')
		return (ft_in_charset("01NSEWPbBtDs", game->map.map[i + 1][j])
			&& ft_in_charset("01NSEWPbBtDs", game->map.map[i][j + 1]));
	else if (ft_in_charset("PbB", game->map.map[i][j]))
	{
		ft_setsprite(game, i, j);
		return (ft_in_charset("01NSEWPbBtDs", game->map.map[i + 1][j])
			&& ft_in_charset("01NSEWPbBtDs", game->map.map[i][j + 1]));
	}
	else if (ft_in_charset("D", game->map.map[i][j]))
	{
		door = (t_door){.frame = 0, .pos = (t_intvec){j, i}, .state = 0};
		ft_add_to_vector(game, &game->doors, &door);
		return (ft_in_charset("01NSEWPbBtDs", game->map.map[i + 1][j])
			&& ft_in_charset("01NSEWPbBtDs", game->map.map[i][j + 1]));
	}
	else if (ft_in_charset("NSEW", game->map.map[i][j]))
	{
		set_player(game->map.map[i][j], i, j, game);
		++(*player_count);
		return (ft_in_charset("01PbBtDs", game->map.map[i + 1][j])
			&& ft_in_charset("01PbBtDs", game->map.map[i][j + 1]));
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
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (!ft_in_charset("012NSEWPbBtDs", game->map.map[i][j]))
				return (0);
			if (!check_one(game, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
