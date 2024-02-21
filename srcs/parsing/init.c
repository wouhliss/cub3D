/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:26:39 by ybelatar          #+#    #+#             */
/*   Updated: 2024/02/21 15:56:04 by wouhliss         ###   ########.fr       */
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
	game->fd = open(path, O_RDONLY);
	if (game->fd == -1)
		panic(FILE_ERR);
	get_info_map(game);
	//put_colors(game);
	//put_textures(game);
	pre_format_map(game);
	if (!check_map(game))
		panic(MAP_ERR);
	format_map(game);
	//set_h_w(game);
}
