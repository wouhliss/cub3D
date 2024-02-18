/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:19:37 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/31 07:22:16 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		panic(MALLOC_ERR);
	mlx_get_screen_size(mlx->mlx, &mlx->width, &mlx->height);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	if (!mlx->win)
	{
		free(mlx->mlx);
		panic(MALLOC_ERR);
	}
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	if (!mlx->img)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		free(mlx->mlx);
		panic(MALLOC_ERR);
	}
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line,
			&mlx->endian);
	if (!mlx->mlx || !mlx->win || !mlx->win || !mlx->addr)
		return (panic("Fail in MLX"), false);
	return (true);
}

static void	init_position(t_player *player, char start_dir)
{
	const double	old_dir_x = player->dir.x;
	const double	old_plane_x = player->plane.x;
	double			to_add;

	if (start_dir == 'W')
		to_add = 0;
	else if (start_dir == 'N')
		to_add = 3 * PI / 2;
	else if (start_dir == 'S')
		to_add = PI / 2;
	else
		to_add = PI;
	player->dir.x = old_dir_x * cos(-to_add) - player->dir.y * sin(-to_add);
	player->dir.y = old_dir_x * sin(-to_add) + player->dir.y * cos(-to_add);
	player->plane.x = old_plane_x * cos(-to_add) - player->plane.y
		* sin(-to_add);
	player->plane.y = old_plane_x * sin(-to_add) + player->plane.y
		* cos(-to_add);
}

int	put_image(t_game *game)
{
	move(game, game->mlx);
	if (game->mlx->refresh == false)
		return (1);
	caster(game->mlx, game->map, game->player);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->mlx->img, 0,
		0);
	game->mlx->refresh = false;
	return (1);
}

bool	start_window(t_mlx *mlx, t_game *game)
{
	if (init(mlx) == false)
		return (false);
	if (!get_textures_walls(mlx, game->map))
		return (false);
	init_position(game->player, game->map->start_direction);
	mlx_hook(mlx->win, ON_DESTROY, NO_MASK, on_destroy, game);
	mlx_hook(mlx->win, ON_KEYPRESS, KEYPRESS_MASK, on_keypress, game);
	mlx_hook(mlx->win, ON_KEYRELEASE, KEYRELEASE_MASK, on_keyrelease, game);
	mlx_loop_hook(mlx->mlx, &put_image, game);
	mlx->refresh = true;
	put_image(game);
	mlx_loop(mlx->mlx);
	return (true);
}
