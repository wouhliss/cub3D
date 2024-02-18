/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:08:08 by pibosc            #+#    #+#             */
/*   Updated: 2024/02/05 20:47:43 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_to_zero_player(t_game *game, t_player *player)
{
	set_pos(&player->pos, 0, 0);
	set_pos(&player->dir, -1, 0);
	set_pos(&player->plane, 0, 0.66);
	player->move_speed = 0.05;
	player->rot_speed = 0.03;
	player->w = false;
	player->a = false;
	player->s = false;
	player->d = false;
	player->r_key = false;
	player->l_key = false;
	player->angle = 0.0;
	game->player = player;
}

void	set_to_zero_mlx(t_game *game, t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
	mlx->addr = NULL;
	mlx->height = -1;
	mlx->width = -1;
	mlx->bpp = -1;
	mlx->size_line = -1;
	mlx->endian = -1;
	mlx->refresh = false;
	game->mlx = mlx;
}

void	set_to_zero_map(t_game *game, t_map *map)
{
	int	i;

	i = 0;
	while (i < 7)
		map->param_lines[i++] = -1;
	map->path_north = NULL;
	map->path_south = NULL;
	map->path_east = NULL;
	map->path_west = NULL;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->total_parameters = 0;
	map->height = 0;
	map->width = 0;
	map->start_coords[0] = -1;
	map->start_coords[1] = -1;
	map->start_direction = '\0';
	map->map = NULL;
	map->first_line_map = -1;
	map->textures[0].img = NULL;
	game->map = map;
}
