/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:19:49 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 12:18:44 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_floorceil(t_game *game, const int w, const int xx)
{
	bool			is_floor;
	t_vec			ray_dir_x;
	t_vec			ray_dir_y;
	int				p;
	double			camZ;
	double			rowDistance;
	t_vec			floor_step;
	t_vec			floor;
	t_intvec		cell;
	t_intvec		t;
	unsigned int	color;

	for (int y = 0; y < HEIGHT; ++y)
	{
		is_floor = y > HEIGHT / 2 + game->p.y;
		ray_dir_x.x = -game->p.dir.x - -game->p.p.x;
		ray_dir_y.x = game->p.dir.y - game->p.p.y;
		ray_dir_x.y = -game->p.dir.x + -game->p.p.x;
		ray_dir_y.y = game->p.dir.y + game->p.p.y;
		p = is_floor ? (y - HEIGHT / 2 - game->p.y) : (HEIGHT / 2 - y
				+ game->p.y);
		camZ = is_floor ? (0.5 * HEIGHT + game->p.jump) : (0.5 * HEIGHT
				- game->p.jump);
		rowDistance = camZ / p;
		floor_step.x = rowDistance * (ray_dir_x.y - ray_dir_x.x) / WIDTH;
		floor_step.y = rowDistance * (ray_dir_y.y - ray_dir_y.x) / WIDTH;
		floor.x = game->p.pos.x + rowDistance * ray_dir_x.x;
		floor.y = game->p.pos.y + rowDistance * ray_dir_y.x;
		floor.x += (floor_step.x * xx);
		floor.y += (floor_step.y * xx);
		for (int x = xx; x < w; ++x)
		{
			cell.x = (int)(floor.x);
			cell.y = (int)(floor.y);
			t.x = (int)(64 * (floor.x - cell.x)) & (64 - 1);
			t.y = (int)(64 * (floor.y - cell.y)) & (64 - 1);
			if (is_floor)
			{
				color = ((unsigned int *)game->textures[0].addr)[game->textures[0].s + 64 * t.y + t.x];
				color = (color >> 1) & 8355711;
				my_mlx_pixel_put(&game->screen, x, y, color);
			}
			else
			{
				color = ((unsigned int *)game->textures[1].addr)[game->textures[1].s + 64 * t.y + t.x];
				color = (color >> 1) & 8355711;
				my_mlx_pixel_put(&game->screen, x, y, color);
			}
			floor.x += floor_step.x;
			floor.y += floor_step.y;
		}
	}
}
