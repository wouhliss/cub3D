/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:38:11 by pibosc            #+#    #+#             */
/*   Updated: 2024/01/31 05:08:37 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		return (clean_mlx(game->mlx, game->map->textures), gc(NULL, 0),
			exit(EXIT_SUCCESS), 1);
	if (keycode == XK_w)
		game->player->w = true;
	if (keycode == XK_a)
		game->player->a = true;
	if (keycode == XK_s)
		game->player->s = true;
	if (keycode == XK_d)
		game->player->d = true;
	if (keycode == XK_Left)
		game->player->l_key = true;
	if (keycode == XK_Right)
		game->player->r_key = true;
	return (1);
}

int	on_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		return (clean_mlx(game->mlx, game->map->textures), gc(NULL, 0),
			exit(EXIT_SUCCESS), 1);
	if (keycode == XK_w)
		game->player->w = false;
	if (keycode == XK_a)
		game->player->a = false;
	if (keycode == XK_s)
		game->player->s = false;
	if (keycode == XK_d)
		game->player->d = false;
	if (keycode == XK_Left)
		game->player->l_key = false;
	if (keycode == XK_Right)
		game->player->r_key = false;
	return (1);
}

int	on_mousepress(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->player->a = true;
	if (button == 3)
		game->player->d = true;
	return (1);
}

int	on_mouserelease(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->player->a = false;
	if (button == 3)
		game->player->d = false;
	return (1);
}

int	on_destroy(t_game *game)
{
	(void)game;
	clean_mlx(game->mlx, game->map->textures);
	gc(NULL, 0);
	exit(EXIT_SUCCESS);
	return (1);
}
