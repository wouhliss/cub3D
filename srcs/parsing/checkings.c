/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:08:21 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/30 03:50:40 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// typedef int t_moha __attribute__((ext_vector_type(2)));

// t_moha avion;
// t_moha bateau;

// avion.x = 3
// avion.y = 5

// avion *= 2;

// avion.x = 6
// avion.y = 10

// bateau = 4;

// bateau.x et bateau.y == 4

// bateau.y 10;

// avion.yx += bateau;

// avion.y += bateau.x
// avion.x += bateau.y

int	ft_in_charset(char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	set_player(char c, int i, int j, t_game *game)
{
	game->map.s_dir = c;
	game->map.s_pos = (t_vec){j + 0.5, i + 0.5};
	game->p.pos = (t_vec){j + 0.5, i + 0.5};
	if (c == 'N')
	{
		game->p.dir = (t_vec){0, -1};
		game->p.plane = (t_vec){-0.66, 0};
	}
	else if (c == 'S')
	{
		game->p.dir = (t_vec){0, 1};
		game->p.plane = (t_vec){0.66, 0};
	}
	else if (c == 'W')
	{
		game->p.dir = (t_vec){1, 0};
		game->p.plane = (t_vec){0, -0.66};
	}
	else if (c == 'E')
	{
		game->p.dir = (t_vec){-1, 0};
		game->p.plane = (t_vec){0, 0.66};
	}
}

int	check_one(t_game *game, int i, int j, int *player_count)
{
	t_sprite	sprite;

	if (i == 0 || i == game->length - 1 || j == 0 || j == game->width - 1)
		return (ft_in_charset("12 ", game->map.map[i][j]));
	if (game->map.map[i][j] == '2')
		return (ft_in_charset("12", game->map.map[i + 1][j])
			&& ft_in_charset("12", game->map.map[i][j + 1]));
	else if (game->map.map[i][j] == '0')
		return (ft_in_charset("01NSEWPbB", game->map.map[i + 1][j])
			&& ft_in_charset("01NSEWPbB", game->map.map[i][j + 1]));
	else if (ft_in_charset("PbB", game->map.map[i][j]))
	{
		if (game->map.map[i][j] == 'b')
		{
			sprite = (t_sprite){.type = 2, .vdiff = 200.0, .hr = 2,
				.vr = 2, .hide = 0};
			sprite.pos = (t_vec){j + 0.5, i + 0.5};
			game->map.map[i][j] = '0';
		}
		else if (game->map.map[i][j] == 'B')
		{
			sprite = (t_sprite){.type = 1, .vdiff = 0.0, .hr = 1,
				.vr = 1, .hide = 0};
			sprite.pos = (t_vec){j + 0.5, i + 0.5};
			game->map.map[i][j] = '0';
		}
		else if (game->map.map[i][j] == 'P')
		{
			sprite = (t_sprite){.type = 0, .vdiff = 0.0, .hr = 1,
				.vr = 1, .hide = 0};
			sprite.pos = (t_vec){j + 0.5, i + 0.5};
			game->map.map[i][j] = '0';
		}
		ft_addsprite(game, &sprite);
		return (ft_in_charset("01NSEWPbB", game->map.map[i + 1][j])
			&& ft_in_charset("01NSEWPbB", game->map.map[i][j + 1]));
	}
	else if (ft_in_charset("NSEW", game->map.map[i][j]))
	{
		set_player(game->map.map[i][j], i, j, game);
		++(*player_count);
		sprite = (t_sprite){.type = 3, .vdiff = 0.0, .hr = 1, .vr = 1,
		.hide = 1};
		sprite.pos = game->map.s_pos;
		game->psprite = ft_addsprite(game, &sprite);
		game->map.map[i][j] = '0';
		return (ft_in_charset("01PbB", game->map.map[i + 1][j])
			&& ft_in_charset("01PbB", game->map.map[i][j + 1]));
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
			if (!ft_in_charset("012NSEWPbB", game->map.map[i][j]))
				return (0);
			if (!check_one(game, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
