/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:07:12 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/31 05:12:57 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_colors(t_game *game)
{
	game->map->ceiling_color = create_trgb(0, game->colors_c[1],
			game->colors_c[2], game->colors_c[3]);
	game->map->floor_color = create_trgb(0, game->colors_f[1],
			game->colors_f[2], game->colors_f[3]);
}

void	put_textures(t_game *game)
{
	game->map->path_north = game->textures[0];
	game->map->path_south = game->textures[1];
	game->map->path_west = game->textures[2];
	game->map->path_east = game->textures[3];
}

void	set_h_w(t_game *game)
{
	game->map->height = game->length;
	game->map->width = game->width;
}
