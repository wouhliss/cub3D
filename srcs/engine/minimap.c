/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:36:34 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/26 15:15:35 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

inline void	ft_drawmap(t_game *game, int x, int y)
{
	t_intvec	s_pos;
	t_intvec	pos;

	s_pos = (t_intvec){game->p.pos.x - 5, game->p.pos.y - 5};
	if (s_pos.x < 0)
		s_pos.x = 0;
	if (s_pos.y < 0)
		s_pos.y = 0;
	x = 49;
	while (++x < MINIMAP_WIDTH + 50 && s_pos.x + ((x - 50) >> 3) < game->width)
	{
		pos.x = s_pos.x + ((x - 50) >> 3);
		y = 19;
		while (++y < MINIMAP_HEIGHT + 20 && s_pos.y + ((y - 20) >> 3) < game->length)
		{
			pos.y = s_pos.y + ((y - 20) >> 3);
			if (game->map.map[pos.y][pos.x] == '1')
				my_mlx_pixel_put(&game->screen, x, y, 0x00000000);
			else if (game->map.map[pos.y][pos.x] == '0')
				my_mlx_pixel_put(&game->screen, x, y, 0x00FFFFFF);
			if ((int)game->p.pos.x == pos.x && (int)game->p.pos.y == pos.y)
				my_mlx_pixel_put(&game->screen, x, y, 0x00FF0000);
		}
	}
}
