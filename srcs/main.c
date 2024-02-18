/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/31 07:19:16 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_extension(char *path)
{
	if (!path)
		return (0);
	return (!ft_strcmp(ft_strchr(path, '.'), ".cub"));
}

t_player	*init_player(void)
{
	t_player	*player;

	player = gc(malloc(sizeof(t_player)), 1);
	set_pos(&(player->pos), 3.5, 2.5);
	set_pos(&(player->dir), 0, -1);
	set_pos(&(player->plane), -0.80, 0);
	player->player_x = 0;
	player->map_x = 0;
	player->map_y = 0;
	player->step_x = 0;
	player->step_y = 0;
	set_pos(&(player->side_dist), 0, 0);
	set_pos(&(player->delta_dist), 0, 0);
	player->perp_wall_dist = 0;
	player->side = 0;
	player->move_speed = 0;
	return (player);
}

void	init_game(t_game *game)
{
	game->textures[0] = NULL;
	game->textures[1] = NULL;
	game->textures[2] = NULL;
	game->textures[3] = NULL;
	game->colors_c[0] = 0;
	game->colors_f[0] = 0;
	game->length = 0;
	game->width = 0;
}

int	main(int ac, char **av)
{
	t_game		*game;
	t_mlx		mlx;
	t_map		map;
	t_player	player;

	if (ac != 2)
	{
		ft_dprintf(2, "%s", "Error\nWrong number of args\n");
		return (1);
	}
	if (!check_extension(av[1]))
	{
		ft_dprintf(2, "%s", "Error\nWrong extension\n");
		return (1);
	}
	game = gc(malloc(sizeof(t_game)), 1);
	if (!game)
		panic(MALLOC_ERR);
	set_to_zero_map(game, &map);
	set_to_zero_player(game, &player);
	set_to_zero_mlx(game, &mlx);
	init_game(game);
	init_map(av[1], game);
	start_window(&mlx, game);
	return (0);
}
