/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 04:25:19 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/31 04:55:12 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	l_key(t_mlx *mlx, t_player *player)
{
	const double	old_dir_x = player->dir.x;
	const double	old_plane_x = player->plane.x;

	mlx->refresh = true;
	player->dir.x = old_dir_x * cos(-player->rot_speed) - player->dir.y
		* sin(-player->rot_speed);
	player->dir.y = old_dir_x * sin(-player->rot_speed) + player->dir.y
		* cos(-player->rot_speed);
	player->plane.x = old_plane_x * cos(-player->rot_speed) - player->plane.y
		* sin(-player->rot_speed);
	player->plane.y = old_plane_x * sin(-player->rot_speed) + player->plane.y
		* cos(-player->rot_speed);
	player->angle += player->rot_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
}

void	r_key(t_mlx *mlx, t_player *player)
{
	const double	old_dir_x = player->dir.x;
	const double	old_plane_x = player->plane.x;

	mlx->refresh = true;
	player->dir.x = old_dir_x * cos(player->rot_speed) - player->dir.y
		* sin(player->rot_speed);
	player->dir.y = old_dir_x * sin(player->rot_speed) + player->dir.y
		* cos(player->rot_speed);
	player->plane.x = old_plane_x * cos(player->rot_speed) - player->plane.y
		* sin(player->rot_speed);
	player->plane.y = old_plane_x * sin(player->rot_speed) + player->plane.y
		* cos(player->rot_speed);
	player->angle -= player->rot_speed;
	if (player->angle < 0)
		player->angle = 2 * PI;
}
