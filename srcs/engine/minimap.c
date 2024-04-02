/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:36:34 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/01 16:52:13 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

inline void	ft_drawmap(t_game *game)
{
	t_intvec	s_pos;
	t_intvec	pos;
	t_intvec	draw;

	s_pos = (t_intvec){game->p.pos.x - 10, game->p.pos.y - 10};
	if (s_pos.x < 0)
		s_pos.x = 0;
	if (s_pos.y < 0)
		s_pos.y = 0;
	draw.x = 49;
	while (++draw.x < MINIMAP_WIDTH + 50 && s_pos.x + ((draw.x - 50) >> 3) < game->width)
	{
		pos.x = s_pos.x + ((draw.x - 50) >> 3);
		draw.y = 19;
		while (++draw.y < MINIMAP_HEIGHT + 20 && s_pos.y + ((draw.y - 20) >> 3) < game->length)
		{
			pos.y = s_pos.y + ((draw.y - 20) >> 3);
			if (game->map.map[pos.y][pos.x] == '1')
				my_mlx_pixel_put(&game->screen, draw.x, draw.y, 0x00000000);
			else if (game->map.map[pos.y][pos.x] == 'D')
				my_mlx_pixel_put(&game->screen, draw.x, draw.y, 0x00777777);
			else
				my_mlx_pixel_put(&game->screen, draw.x, draw.y, 0x00FFFFFF);
			if ((int)game->p.pos.x == pos.x && (int)game->p.pos.y == pos.y)
				my_mlx_pixel_put(&game->screen, draw.x, draw.y, 0x00FF0000);
		}
	}
}
