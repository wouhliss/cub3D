/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibosc <pibosc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 04:47:28 by pibosc            #+#    #+#             */
/*   Updated: 2024/02/05 20:20:39 by pibosc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	get_color_r(t_map *map, int id, int texture_x, int texture_y)
{
	return (((unsigned int *)(map->textures[id].addr))[64 * texture_y
		+ texture_x]);
}

int	select_texture_wall(t_player *player)
{
	int	wall_face;

	if (player->hit == 2)
		return (4);
	if (player->side == 0)
	{
		if (player->step_x > 0)
			wall_face = 2;
		else
			wall_face = 3;
	}
	else
	{
		if (player->step_y > 0)
			wall_face = 0;
		else
			wall_face = 1;
	}
	return (wall_face);
}
