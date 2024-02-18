/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:33:43 by pibosc            #+#    #+#             */
/*   Updated: 2024/02/05 20:17:26 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mlx_mpp(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	initialize_line(t_mlx *mlx, t_line *line, t_player *player,
		const int line_height)
{
	line->draw_start = -line_height / 2 + mlx->height / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = line_height / 2 + mlx->height / 2;
	if (line->draw_end >= mlx->height)
		line->draw_end = mlx->height - 1;
	line->texture_number = select_texture_wall(player);
	if (player->side == 0)
		line->wall_x = player->pos.y + player->perp_wall_dist
			* player->ray_dir.y;
	else
		line->wall_x = player->pos.x + player->perp_wall_dist
			* player->ray_dir.x;
	line->wall_x -= floor((line->wall_x));
	line->texture_x = (int)(line->wall_x * (double)64);
	if (player->side == 0 && player->ray_dir.x > 0)
		line->texture_x = 64 - line->texture_x - 1;
	if (player->side == 1 && player->ray_dir.y < 0)
		line->texture_x = 64 - line->texture_x - 1;
	line->step = 1.0 * 64 / line_height;
	line->texture_pos = (line->draw_start - mlx->height / 2 + line_height / 2)
		* line->step;
}

void	draw_3d_walls(t_mlx *mlx, t_map *map, t_player *player, int x)
{
	const int	line_height = (int)(mlx->height / player->perp_wall_dist);
	int			y;
	t_line		line;

	initialize_line(mlx, &line, player, line_height);
	y = 0;
	while (y < line.draw_start)
		mlx_mpp(mlx, x, y++, map->ceiling_color);
	y = line.draw_start;
	while (y < line.draw_end)
	{
		line.texture_y = (int)line.texture_pos & 63;
		line.texture_pos += line.step;
		line.color = get_color_r(map, line.texture_number, line.texture_x,
				line.texture_y);
		if (player->side == 1)
			line.color = (line.color >> 1) & 8355711;
		mlx_mpp(mlx, x, y, line.color);
		++y;
	}
	y = line.draw_end;
	while (y < mlx->height)
		mlx_mpp(mlx, x, y++, map->floor_color);
}
