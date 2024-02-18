/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:06:35 by pibosc            #+#    #+#             */
/*   Updated: 2024/02/05 20:19:52 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	destroy_wall_images(t_mlx *mlx, t_map *map, const int ind)
{
	int	i;

	i = 1;
	mlx_destroy_image(mlx->mlx, map->textures[0].img);
	map->textures[0].img = NULL;
	while (i < ind)
		mlx_destroy_image(mlx->mlx, map->textures[i++].img);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	panic(MAP_ERR);
}

static bool	get_addresses_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		map->textures[i].addr = mlx_get_data_addr(map->textures[i].img,
				&(map->textures[i].bpp), &(map->textures[i].size_line),
				&(map->textures[i].endian));
		if (!map->textures[i].addr)
			return (false);
		++i;
	}
	return (true);
}

bool	get_textures_walls(t_mlx *mlx, t_map *map)
{
	map->textures[0].img = mlx_xpm_file_to_image(mlx->mlx, map->path_north,
			&(map->textures[0].width), &(map->textures[0].height));
	if (!map->textures[0].img
		|| map->textures[0].width != 64 || map->textures[0].height != 64)
		return (destroy_wall_images(mlx, map, 0), false);
	map->textures[1].img = mlx_xpm_file_to_image(mlx->mlx, map->path_south,
			&(map->textures[1].width), &(map->textures[1].height));
	if (!map->textures[1].img
		|| map->textures[1].width != 64 || map->textures[1].height != 64)
		return (destroy_wall_images(mlx, map, 1), false);
	map->textures[2].img = mlx_xpm_file_to_image(mlx->mlx, map->path_west,
			&(map->textures[2].width), &(map->textures[2].height));
	if (!map->textures[2].img
		|| map->textures[2].width != 64 || map->textures[2].height != 64)
		return (destroy_wall_images(mlx, map, 2), false);
	map->textures[3].img = mlx_xpm_file_to_image(mlx->mlx, map->path_east,
			&(map->textures[3].width), &(map->textures[3].height));
	if (!map->textures[3].img || !get_addresses_walls(map)
		|| map->textures[3].width != 64 || map->textures[3].height != 64)
		return (destroy_wall_images(mlx, map, 3), false);
	return (true);
}

void	clean_mlx(t_mlx *mlx, t_texture textures[5])
{
	mlx_destroy_image(mlx->mlx, textures[0].img);
	mlx_destroy_image(mlx->mlx, textures[1].img);
	mlx_destroy_image(mlx->mlx, textures[2].img);
	mlx_destroy_image(mlx->mlx, textures[3].img);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}
