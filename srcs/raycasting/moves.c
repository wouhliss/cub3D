/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:41:33 by pibosc            #+#    #+#             */
/*   Updated: 2024/02/05 21:08:11 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	up(t_game *game, t_mlx *mlx)
{
	int	index_x;
	int	index_y;

	mlx->refresh = true;
	index_x = game->player->pos.x + game->player->dir.x
		* game->player->move_speed;
	index_y = game->player->pos.y + game->player->dir.y
		* game->player->move_speed;
	if (ft_strchr("0NEWS",
			game->map->map[(int)(game->player->pos.y)][index_x]))
		game->player->pos.x += game->player->dir.x * game->player->move_speed;
	if (ft_strchr("0NEWS",
			game->map->map[index_y][(int)(game->player->pos.x)]))
		game->player->pos.y += game->player->dir.y * game->player->move_speed;
}

static void	left(t_game *game, t_mlx *mlx)
{
	double	index_x;
	double	index_y;

	mlx->refresh = true;
	index_x = (game->player->pos.x + game->player->dir.y
			* game->player->move_speed);
	index_y = (game->player->pos.y - game->player->dir.x
			* game->player->move_speed);
	if (ft_strchr("0NEWS", game->map->map[(int)(index_y)][(int)index_x]))
	{
		game->player->pos.x += game->player->dir.y * game->player->move_speed;
		game->player->pos.y -= game->player->dir.x * game->player->move_speed;
	}
}

static void	down(t_game *game, t_mlx *mlx)
{
	int	index_x;
	int	index_y;

	mlx->refresh = true;
	index_x = game->player->pos.x - game->player->dir.x
		* game->player->move_speed;
	index_y = game->player->pos.y - game->player->dir.y
		* game->player->move_speed;
	if (ft_strchr("0NEWS",
			game->map->map[(int)(game->player->pos.y)][index_x]))
		game->player->pos.x -= game->player->dir.x * game->player->move_speed;
	if (ft_strchr("0NEWS",
			game->map->map[index_y][(int)(game->player->pos.x)]))
		game->player->pos.y -= game->player->dir.y * game->player->move_speed;
}

static void	right(t_game *game, t_mlx *mlx)
{
	double	index_x;
	double	index_y;

	mlx->refresh = true;
	index_x = (game->player->pos.x - game->player->dir.y
			* game->player->move_speed);
	index_y = (game->player->pos.y + game->player->dir.x
			* game->player->move_speed);
	if (ft_strchr("0NEWS", game->map->map[(int)(index_y)][(int)index_x]))
	{
		game->player->pos.x -= game->player->dir.y * game->player->move_speed;
		game->player->pos.y += game->player->dir.x * game->player->move_speed;
	}
}

void	move(t_game *game, t_mlx *mlx)
{
	if (game->player->w == true)
		up(game, mlx);
	if (game->player->a == true)
		left(game, mlx);
	if (game->player->s == true)
		down(game, mlx);
	if (game->player->d == true)
		right(game, mlx);
	if (game->player->r_key == true)
		r_key(mlx, game->player);
	if (game->player->l_key == true)
		l_key(mlx, game->player);
}
