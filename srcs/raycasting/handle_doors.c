/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 04:25:07 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/31 04:54:53 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	valid_coordinates(t_map *map, int x, int y)
{
	return (x >= 0 && y >= 0 && x < map->width && y < map->height);
}

static void	set_coords(int x, int y, int coords[2])
{
	coords[0] = x;
	coords[1] = y;
}

static bool	detect_door(t_map *map, t_player *player, int coords[2])
{
	const int	map_x = player->pos.x;
	const int	map_y = player->pos.y;

	if (valid_coordinates(map, map_x, map_y - 1) && ft_in_charset("23",
			map->map[map_y - 1][map_x]) && 5 * PI / 4 < player->angle
		&& player->angle <= 7 * PI / 4)
		return (set_coords(map_x, map_y - 1, coords), true);
	if (valid_coordinates(map, map_x, map_y + 1) && ft_in_charset("23",
			map->map[map_y + 1][map_x]) && PI / 4 < player->angle
		&& player->angle <= 3 * PI / 4)
		return (set_coords(map_x, map_y + 1, coords), true);
	if (valid_coordinates(map, map_x - 1, map_y) && ft_in_charset("23",
			map->map[map_y][map_x - 1]) && ((7 * PI / 4 < player->angle
				&& player->angle <= 2 * PI / 4) || (0 <= player->angle
				&& player->angle <= PI / 4)))
		return (set_coords(map_x - 1, map_y, coords), true);
	if (valid_coordinates(map, map_x + 1, map_y) && ft_in_charset("23",
			map->map[map_y][map_x + 1]) && 3 * PI / 4 < player->angle
		&& player->angle <= 5 * PI / 4)
		return (set_coords(map_x + 1, map_y, coords), true);
	return (false);
}

bool	door(t_map *map, t_player *player)
{
	int	coords[2];

	if (detect_door(map, player, coords) == false)
		return (false);
	return (true);
}

void	door_action(t_mlx *mlx, t_map *map, t_player *player)
{
	int	coords[2];

	if (detect_door(map, player, coords))
	{
		if (map->map[coords[1]][coords[0]] == '2')
			map->map[coords[1]][coords[0]] = '3';
		else if (map->map[coords[1]][coords[0]] == '3')
			map->map[coords[1]][coords[0]] = '2';
		mlx->refresh = true;
	}
}
