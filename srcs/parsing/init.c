/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:26:39 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/12 15:03:39 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	display_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (!tab)
// 		return ;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// }

// void	display_misc(t_game *game)
// {
// 	printf("NO : %s\n", game->textures[0]);
// 	printf("SO : %s\n", game->textures[1]);
// 	printf("WE : %s\n", game->textures[2]);
// 	printf("EA : %s\n", game->textures[3]);
// 	printf("C : %d, ", game->colors_c[1]);
// 	printf("%d, ", game->colors_c[2]);
// 	printf("%d\n", game->colors_c[3]);
// 	printf("F : %d, ", game->colors_f[1]);
// 	printf("%d, ", game->colors_f[2]);
// 	printf("%d\n", game->colors_f[3]);
// }

// void	display_player(t_pos pos)
// {
// 	printf("X : %f\n", pos.x);
// 	printf("Y : %f\n", pos.y);
// }

void	init_map(char *path, t_game *game)
{
	int	i;

	ft_create_vector(&game->doors, DOOR, sizeof(t_door));
	ft_create_vector(&game->sprites, SPRITE, sizeof(t_sprite));
	ft_create_vector(&game->projectiles, PROJECTILE, sizeof(t_projectile));
	game->fd = open(path, O_RDONLY);
	if (game->fd == -1)
		panic(FILE_ERR);
	get_info_map(game);
	put_colors(game);
	pre_format_map(game);
	if (!check_map(game))
		panic(CHAR_ERR);
	format_map(game);
	i = -1;
	while (++i < WTEXTURES)
	{
		game->wt[i].addr = 0;
		game->wt[i].img = 0;
	}
	i = -1;
	while (++i < STEXTURES)
	{
		game->st[i].addr = 0;
		game->st[i].img = 0;
	}
	i = -1;
	while (++i < PTEXTURES)
	{
		game->ptextures[i].addr = 0;
		game->ptextures[i].img = 0;
	}
}
