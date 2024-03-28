/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:07:12 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/28 15:53:42 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

inline int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_colors(t_game *game)
{
	game->map.c_color = create_trgb(0, game->colors_c[1], game->colors_c[2],
			game->colors_c[3]);
	game->map.f_color = create_trgb(0, game->colors_f[1], game->colors_f[2],
			game->colors_f[3]);
}
